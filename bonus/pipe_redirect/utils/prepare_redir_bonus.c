/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_redir_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 11:26:53 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/21 14:01:45 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell_bonus.h"

void		prepare_redirect_put(int (*fd)[2], int *backup,
				t_cmdlst *lst, t_minishell *info)
{
	t_cmdlst	*begin;

	begin = lst;
	while (lst && is_redir(lst->type) && (lst)->next)
	{
		if (backup[lst->fd] == -1 &&
		(backup[lst->fd] = dup(lst->fd)) == -1)
			;
		if (fd[lst->fd][1] == -1 &&
		dup2(fd[lst->fd][0], lst->fd) == -1)
			;
		fd[lst->fd][1] = 1;
		lst = (lst)->next->next;
	}
	lst = begin;
	while (lst && is_redir(lst->type) && (lst)->next)
	{
		if (lst->fd > 3)
			close(fd[lst->fd][0]);
		lst = (lst)->next->next;
	}
}
