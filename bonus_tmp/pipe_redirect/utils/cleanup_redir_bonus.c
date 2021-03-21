/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_redir_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 11:26:47 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/21 16:52:07 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell_bonus.h"

void		cleanup_redirect_put(int (*fd)[2], int *backup,
				t_cmdlst *lst, t_minishell *info)
{
	t_cmdlst	*begin;

	begin = lst;
	while (lst && is_redir(lst->type) && (lst)->next)
	{
		if (dup2(backup[lst->fd], lst->fd) == -1)
			;
		lst = (lst)->next->next;
	}
	lst = begin;
	while (lst && is_redir(lst->type) && (lst)->next)
	{
		close(fd[lst->fd][0]);
		close(backup[lst->fd]);
		lst = (lst)->next->next;
	}
}
