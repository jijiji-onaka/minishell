/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlst_add_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 21:28:43 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/17 04:37:54 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell_bonus.h"

static t_cmdlst	*cmd_lstlast(t_cmdlst *lst)
{
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

static void		cmd_lstadd_back(t_cmdlst **begin, t_cmdlst *new)
{
	t_cmdlst *last;

	if (!*begin)
	{
		*begin = new;
		return ;
	}
	last = cmd_lstlast(*begin);
	last->next = new;
}

static t_cmdlst	*make_cmdlst(char **command, int type, int fd)
{
	t_cmdlst	*cmd;

	if (!(cmd = malloc(sizeof(t_cmdlst))))
		return (NULL);
	cmd->type = type;
	if (is_redir(type))
		cmd->fd = fd;
	cmd->arg = command;
	cmd->checker_pipe = false;
	cmd->checker_redir = false;
	cmd->next = NULL;
	return (cmd);
}

bool			cmdlst_add_back(t_minishell *info,
						char **command, int type, int fd)
{
	t_cmdlst	*cmd;

	if (!(cmd = make_cmdlst(command, type, fd)))
	{
		ptr_2d_free((void***)&command, -1);
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	}
	cmd_lstadd_back(&(info->cmd_lst), cmd);
	return (true);
}
