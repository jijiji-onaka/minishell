/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting_for_input_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 01:01:05 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/20 01:11:17 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

static void	preparation(int *backup, char **command,
					char *buf, t_minishell *info)
{
	if ((*backup = dup(STDIN_FILENO)) == -1)
		all_free_exit(info, ERR_DUP, __LINE__, __FILE__);
	if (!(*command = ft_strdup("")))
	{
		if (ft_close(backup) == false)
			all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	}
	*buf = '\0';
	g_signal.reading = true;
}

static void	check_return_value(ssize_t rc, char **command, char buf, \
			t_minishell *info)
{
	if (rc != 0)
	{
		if (!(*command = re_strjoinch(command, buf)))
			all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	}
	else if (rc == 0 && (*command)[0] == '\0')
		ctrl_d_exit(command, info);
}

static void	clean_up(int *backup, char **command, t_minishell *info)
{
	if (!g_signal.reading)
		if ((dup2(*backup, STDIN_FILENO)) == -1)
		{
			ptr_free((void**)command);
			all_free_exit(info, ERR_DUP2, __LINE__, __FILE__);
		}
	if (ft_close(backup) == false)
	{
		ptr_free((void**)command);
		all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	}
}

char		*waiting_for_input(t_minishell *info)
{
	char	*command;
	char	buf;
	ssize_t	rc;
	int		backup;

	preparation(&backup, &command, &buf, info);
	while (g_signal.reading)
	{
		if ((rc = safe_read(&buf, &command, info)) && buf == '\n')
			break ;
		ctrl_d_rm(&command, info);
		check_return_value(rc, &command, buf, info);
	}
	clean_up(&backup, &command, info);
	if (!g_signal.reading)
		return (reset_prompt(&command, NULL));
	return (command);
}
