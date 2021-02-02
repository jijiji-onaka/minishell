/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 21:03:13 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 17:48:42 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** 構造体に持ったコマンドのタイプを元にそれに応じた処理を振り分ける関数
*/

bool		execute_each_command(t_minishell_info *info, t_cmdlst *cmd)
{
	int	type;

	type = cmd->type;
	if (type == BIN)
		exec_bin(info, cmd->arg);
	else if (type == EXIT)
		exec_exit(info);
	else if (type == PWD)
		exec_pwd(info);
	else if (type == ECHO)
		exec_echo(info, cmd);
	else if (type == CD)
		exec_cd(info, cmd);
	else if (type == ENV)
		exec_env(info, cmd->arg[1]);
	else if (type == EXPORT)
		exec_export(info, cmd->arg);
	else if (type == UNSET)
		exec_unset(info, cmd->arg);
	return (true);
}

void		execute_each_command_loop(t_minishell_info *info)
{
	while (info->cmd_lst)
	{
		if (info->cmd_lst->type == OUTPUT)
			just_open_file(info, info->cmd_lst);
		else if (info->cmd_lst->next && (info->cmd_lst->next->type == OUTPUT ||
				info->cmd_lst->next->type == DB_OUTPUT ||
				info->cmd_lst->next->type == INPUT ||
				info->cmd_lst->next->type == STDERR_OUTPUT ||
				info->cmd_lst->next->type == STDERR_DB_OUTPUT))
			info->cmd_lst = redirect_sep(info, &(info->cmd_lst));
		else if (info->cmd_lst->next && info->cmd_lst->next->type == PIPE)
			info->cmd_lst = pipe_sep(info, &(info->cmd_lst));
		else
			execute_each_command(info, info->cmd_lst);
		if (info->cmd_lst == NULL)
			break ;
		skip_lst_and_free(&(info->cmd_lst), 1);
	}
	info->cmd_lst = NULL;
}
