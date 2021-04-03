/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting_for_next_command_bonus.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 16:00:32 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/04 03:01:28 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

static char	*preparation(int *backup, \
			t_cmd_grp *cmd_grp_info, char ***cmd_grp, int array_size)
{
	char	*res;

	if (!(res = ft_strdup("")))
		all_free_exit(&(g_global.info), ERR_MALLOC, __LINE__, __FILE__);
	display_what_is_waiting_for('|', &res, NULL, &(g_global.info));
	if ((*backup = dup(STDIN)) == -1)
	{
		ptr_free((void**)&res);
		all_free_exit(&(g_global.info), ERR_DUP, __LINE__, __FILE__);
	}
	cmd_grp_info->cmd_grp = cmd_grp;
	cmd_grp_info->array_size = array_size;
	g_global.reading = true;
	return (res);
}

static void	clean_up(int *backup, char **inputs, t_minishell *info)
{
	if (!g_global.reading)
		if ((dup2(*backup, STDIN)) == -1)
		{
			ptr_free((void**)inputs);
			all_free_exit(info, ERR_DUP2, __LINE__, __FILE__);
		}
	if (ft_close(backup) == false)
	{
		ptr_free((void**)inputs);
		all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	}
	ptr_free((void **)inputs);
}

static bool	press_newline(char **inputs,
					t_cmd_grp *cmd_grp_info, t_minishell *info)
{
	int	rc;

	rc = check_more_pipe(inputs, cmd_grp_info, info);
	if (rc != NEXT_CMD && rc != NEWLINE)
	{
		if (rc == false)
			ptr_2d_free((void***)(cmd_grp_info->cmd_grp), -1);
		info->cmd_lst_num = cmd_grp_info->array_size;
		return (false);
	}
	if (!(*inputs = re_strdup(inputs, " ")))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	display_what_is_waiting_for('|', inputs, NULL, info);
	return (NEXT_CMD);
}

static void	*press_eof(char **inputs, t_cmd_grp *cmd_grp_info,
				int *backup, t_minishell *info)
{
	ptr_free((void **)inputs);
	clean_up(backup, inputs, info);
	if (write(STDERR, "minishell: syntax error: unexpected end of file\n"
, 48) < 48)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	ptr_2d_free((void***)(cmd_grp_info->cmd_grp), -1);
	return (NULL);
}

char		*waiting_for_next_command(char ***cmd_grp, int array_size,
								t_minishell *info)
{
	ssize_t		rc;
	char		buf;
	char		*inputs;
	t_cmd_grp	cmd_grp_info;
	int			backup;

	inputs = preparation(&backup, &cmd_grp_info, cmd_grp, array_size);
	while (g_global.reading)
	{
		if ((rc = safe_read(&buf, &inputs, info)) < 0)
			break ;
		ctrl_d_rm(&inputs, info);
		if (rc == 0 && inputs[0] == '\0')
			return (press_eof(&inputs, &cmd_grp_info, &backup, info));
		if (buf == '\n' && !(rc = press_newline(&inputs, &cmd_grp_info, info)))
			return (NULL);
		if (buf != '\n' && !(inputs = re_strjoinch(&inputs, buf)))
			all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	}
	clean_up(&backup, &inputs, info);
	ptr_2d_free((void***)(cmd_grp_info.cmd_grp), -1);
	return (reset_prompt(&inputs, NULL));
}
