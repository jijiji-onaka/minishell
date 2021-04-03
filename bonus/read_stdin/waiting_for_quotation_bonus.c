/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting_for_quotation_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 00:23:07 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/04 03:01:09 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

static char	*preparation(char first_quo, char **command, int *backup,
					t_minishell *info)
{
	char	*res;

	if (!(res = ft_strdup("\0")))
	{
		ptr_free((void**)command);
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	}
	display_what_is_waiting_for(first_quo, &res, command, info);
	if ((*backup = dup(STDIN)) == -1)
	{
		ptr_free((void**)command);
		ptr_free((void**)res);
		all_free_exit(info, ERR_DUP, __LINE__, __FILE__);
	}
	g_global.reading = true;
	info->ptr_for_free = *command;
	return (res);
}

static void	clean_up(int *backup, char **inputs, t_minishell *info)
{
	if (!g_global.reading)
		if ((dup2(*backup, STDIN)) == -1)
		{
			ptr_free((void**)inputs);
			ptr_free((void**)info->ptr_for_free);
			info->ptr_for_free = NULL;
			all_free_exit(info, ERR_DUP2, __LINE__, __FILE__);
		}
	if (ft_close(backup) == false)
	{
		ptr_free((void**)inputs);
		ptr_free((void**)info->ptr_for_free);
		info->ptr_for_free = NULL;
		all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	}
	info->ptr_for_free = NULL;
	ptr_free((void **)inputs);
}

static void	*press_eof(char match, char **inputs, \
				int *backup, t_minishell *info)
{
	ptr_free((void **)inputs);
	ptr_free((void **)&(info->ptr_for_free));
	clean_up(backup, inputs, info);
	if (write(2, "minishell: unexpected EOF while looking for matching `", 54)
				< 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (write(2, &match, 1) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (write(2, "`\nminishell: syntax error: unexpected end of file\n", 50)
				< 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	return (NULL);
}

static bool	press_newline(char *first_quo, char **inputs, \
					char **command, t_minishell *info)
{
	if (is_valid_quotations(inputs, first_quo) != false)
		return (true);
	if (!(*command = re_str3join(command, *command, "\n", *inputs)))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	if (!(*inputs = re_strdup(inputs, "\0")))
	{
		ptr_free((void**)command);
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	}
	display_what_is_waiting_for(*first_quo, inputs, command, info);
	return (false);
}

char		*waiting_for_quotation(char first_quo, char **command, \
						t_minishell *info)
{
	ssize_t		rc;
	char		buf;
	char		*inputs;
	int			backup;

	inputs = preparation(first_quo, command, &backup, info);
	buf = '\0';
	while (g_global.reading)
	{
		if ((rc = safe_read(&buf, &inputs, info)) < 0)
			break ;
		ctrl_d_rm(&inputs, info);
		if (rc == 0 && inputs[0] == '\0')
			return (press_eof(first_quo, &inputs, &backup, info));
		if (buf == '\n' && press_newline(&first_quo, &inputs, command, info))
			break ;
		if (buf != '\n' && rc != 0 && !(inputs = re_strjoinch(&inputs, buf)))
			all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	}
	if (!(*command = re_str3join(command, *command, "\n", inputs)))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	clean_up(&backup, &inputs, info);
	if (!g_global.reading)
		return (reset_prompt(command, NULL));
	return (*command);
}
