/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting_for_next_command.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 16:00:32 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 17:45:09 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_more_pipe(char **inputs, t_cmd_grp *cmd_grp_info,
								t_minishell_info *info)
{
	char	**split;
	int		i;

	if ((*inputs)[0] == '\0')
		return (NEWLINE);
	if (!(split = split_each_parts(*inputs)))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	ptr_free((void **)inputs);
	i = 0;
	while (split[i])
	{
		if (i != 0 && split[i][0] == '|' && split[i][1] != '|' && !split[i + 1])
			return (add_command_group(split, cmd_grp_info, i + 1, info));
		if (is_output_format_error(&split, i, info) == false)
			return (false);
		if (is_pipe_format_error(&split, i, info) == false)
			return (false);
		if (is_semicolon_format_error(&split, i, info) == false)
			return (false);
		i++;
	}
	add_command_group(split, cmd_grp_info, i, info);
	return (true);
}

static char	*prepare_in_advance(t_minishell_info *info, \
			t_cmd_grp *cmd_grp_info, char ***cmd_grp, int array_size)
{
	char	*res;

	cmd_grp_info->cmd_grp = cmd_grp;
	cmd_grp_info->array_size = array_size;
	if (write(1, "> ", 2) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (!(res = ft_strdup("")))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	return (res);
}

static bool	check_buf_and_return_value(ssize_t rc, char **inputs, char buf, \
			t_minishell_info *info)
{
	if (rc != 0)
	{
		if (buf != ' ' && buf != '\n')
			*inputs = re_strjoinch(inputs, buf);
	}
	else if (rc == 0 && ((*inputs) == NULL || (*inputs)[0] == '\0'))
	{
		ptr_free((void **)inputs);
		syntax_error(SYNTAX_EOL_NUM, info);
		return (false);
	}
	return (true);
}

static bool	do_when_input_char_equal_newline(char **inputs,
					t_cmd_grp *cmd_grp_info, t_minishell_info *info)
{
	int	rc;

	rc = check_more_pipe(inputs, cmd_grp_info, info);
	if (rc != NEXT_CMD && rc != NEWLINE)
	{
		if (rc == false)
			*(cmd_grp_info->cmd_grp) = NULL;
		return (false);
	}
	write(1, "> ", 2);
	return (NEXT_CMD);
}

int			waiting_for_next_command(char ***cmd_grp, int array_size,
								t_minishell_info *info)
{
	ssize_t		rc;
	char		buf;
	char		*inputs;
	t_cmd_grp	cmd_grp_info;

	inputs = prepare_in_advance(info, &cmd_grp_info, cmd_grp, array_size);
	while ((rc = safe_read(&buf, &inputs, info)) >= 0)
	{
		if (write(1, "\033[0K", 4) < 0)
		{
			ptr_free((void **)&inputs);
			all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
		}
		if (check_buf_and_return_value(rc, &inputs, buf, info) == false)
		{
			ptr_2d_free((void***)cmd_grp_info.cmd_grp, cmd_grp_info.array_size);
			return (false);
		}
		if (buf == '\n')
			if (!do_when_input_char_equal_newline(&inputs, &cmd_grp_info, info))
				return (cmd_grp_info.array_size);
	}
	return (false);
}
