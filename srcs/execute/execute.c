/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 21:03:13 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/24 00:36:05 by tjinichi         ###   ########.fr       */
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

static int	return_index(int type)
{
	if (type == BIN)
		return (0);
	else if (type == EXIT)
		return (1);
	else if (type == PWD)
		return (2);
	else if (type == CMD_ECHO)
		return (3);
	else if (type == CD)
		return (4);
	else if (type == ENV)
		return (5);
	else if (type == EXPORT)
		return (6);
	else if (type == UNSET)
		return (7);
	return (END_OF_THE_WORLD);
}

bool		execute_command(t_minishell *info, t_cmdlst *cmd)
{
	int		type;
	void	(*const exec_command[])(t_minishell *, t_cmdlst *) = {
		exec_bin, exec_exit, exec_pwd, exec_echo, exec_cd, exec_env,
		exec_export, exec_unset,
	};

	if ((cmd)->type == SEMICOLON)
		return (true);
	type = cmd->type;
	if (final_cmd_check(&type, cmd, info) == false)
		return (true);
	if (is_redir(type) || type == SEMICOLON || type == PIPE)
		return (write(STDOUT_FILENO, "my minishell is failed (T_T)\n", 29));
	exec_command[return_index(type)](info, cmd);
	info->ptr_for_free = NULL;
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

void		execute_command_loop(t_minishell *info)
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
