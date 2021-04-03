/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 21:03:13 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/04 03:01:19 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

static bool	final_cmd_check(int *type, t_cmdlst *cmd, t_minishell *info)
{
	int		i;
	int		tmp_type;

	if (at_first_change_only_env(cmd, type, info) == false)
		return (false);
	i = -1;
	while (cmd->arg[++i])
	{
		if (change_astarisk(&(cmd->arg[i]), info, i) == true)
			change_env_and_quo_and_slash(&(cmd->arg[i]), info);
	}
	tmp_type = binary_search(cmd->arg[0]);
	if (!((tmp_type >= 1 && tmp_type <= 4) || tmp_type == PIPE))
		*type = tmp_type;
	return (true);
}

bool		execute_command(t_minishell *info, t_cmdlst **cmd)
{
	int		type;
	void	(*const exec_command[])(t_minishell *, t_cmdlst *) = {
		exec_bin, exec_exit, exec_pwd, exec_echo, exec_cd, exec_env,
		exec_export, exec_unset,
	};

	type = (*cmd)->type;
	if ((*cmd)->type == SEMICOLON)
		return (true);
	if (final_cmd_check(&type, *cmd, info) == false)
		return (true);
	if (is_redir(type) || type == SEMICOLON || type == PIPE || type == DB_AND)
		return (write(STDOUT, "my minishell is failed (T_T)\n", 29));
	exec_command[return_index(type)](info, *cmd);
	info->ptr_for_free = NULL;
	if ((*cmd) && (*cmd)->next && (*cmd)->next->type == DB_AND)
		*cmd = do_and(cmd);
	if ((*cmd) && (*cmd)->next && (*cmd)->next->type == DB_PIPE)
		*cmd = do_db_pipe(cmd);
	return (true);
}

static bool	is_after_pipe(t_cmdlst *lst)
{
	while (lst)
	{
		if (lst->type == SEMICOLON || lst->type == DB_AND)
			return (false);
		else if (lst->type == PIPE)
			return (true);
		lst = lst->next;
	}
	return (false);
}

void		do_(t_cmdlst **lst, t_minishell *info)
{
	if ((*lst)->type == DB_AND)
		do_and((lst));
	else if ((*lst)->type == DB_PIPE)
		do_db_pipe(lst);
	else
		execute_command(info, lst);
}

void		execute_command_loop(t_minishell *info)
{
	t_cmdlst	*lst;

	lst = info->cmd_lst;
	while (lst)
	{
		if (is_after_pipe(lst))
		{
			if (NULL == my_pipe(info, &(lst), 2))
				break ;
		}
		if (is_redir(lst->type))
		{
			if (NULL == redir_first(info, &(lst)))
				break ;
		}
		if (lst->next && is_redir(lst->next->type))
		{
			if (NULL == my_redirect(info, &(lst)))
				break ;
		}
		else
			do_(&lst, info);
		if (lst)
			lst = lst->next;
	}
}
