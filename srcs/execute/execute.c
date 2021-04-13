/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 21:03:13 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/10 16:34:23 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	final_cmd_check(int *type, t_cmdlst *cmd, t_minishell *info)
{
	int		i;
	int		tmp_type;

	if (at_first_change_only_env(cmd, type, info) == false)
		return (false);
	i = -1;
	while (cmd->arg[++i])
		change_env_and_quo_and_slash(&(cmd->arg[i]), info);
	tmp_type = binary_search(cmd->arg[0]);
	if (!((tmp_type >= 1 && tmp_type <= 4) || tmp_type == PIPE))
		*type = tmp_type;
	return (true);
}

bool	execute_command(t_minishell *info, t_cmdlst *cmd)
{
	if (cmd->type == SEMICOLON)
		return (true);
	if (final_cmd_check(&(cmd->type), cmd, info) == false)
		return (true);
	if (is_redir(cmd->type) || cmd->type == SEMICOLON || cmd->type == PIPE)
		return (write(STDOUT, "my minishell is failed (T_T)\n", 29));
	if (cmd->type == BIN)
		exec_bin(info, cmd);
	else if (cmd->type == EXIT)
		exec_exit(info, cmd);
	else if (cmd->type == PWD)
		exec_pwd(info, cmd);
	else if (cmd->type == CMD_ECHO)
		exec_echo(info, cmd);
	else if (cmd->type == CD)
		exec_cd(info, cmd);
	else if (cmd->type == ENV)
		exec_env(info, cmd);
	else if (cmd->type == EXPORT)
		exec_export(info, cmd);
	else if (cmd->type == UNSET)
		exec_unset(info, cmd);
	return (true);
}

static bool	is_after_pipe(t_cmdlst *lst)
{
	while (lst)
	{
		if (lst->type == SEMICOLON)
			return (false);
		else if (lst->type == PIPE)
			return (true);
		lst = lst->next;
	}
	return (false);
}

void	execute_command_loop(t_minishell *info)
{
	t_cmdlst	*lst;

	lst = info->cmd_lst;
	while (lst && !(info->exit_too_arg))
	{
		if (is_after_pipe(lst))
		{
			if (NULL == my_pipe(info, &(lst), 2))
				break ;
		}
		else if (is_redir(lst->type))
		{
			if (NULL == redir_first(info, &(lst)))
				break ;
		}
		else if (lst->next && is_redir(lst->next->type))
		{
			if (NULL == my_redirect(info, &(lst)))
				break ;
		}
		else
			execute_command(info, lst);
		lst = lst->next;
	}
}
