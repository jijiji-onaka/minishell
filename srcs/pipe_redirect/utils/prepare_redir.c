/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 11:26:53 by tjinichi          #+#    #+#             */
/*   Updated: 2021/05/16 15:03:48 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	prepare_redirect_put(int **fd, int *backup,
				t_cmdlst *lst, t_minishell *info)
{
	t_cmdlst	*begin;

	(void)info;
	begin = lst;
	while (lst && is_redir(lst->type) && (lst)->next)
	{
		if (backup[lst->fd] == -1)
			backup[lst->fd] = dup(lst->fd);
		if (fd[lst->fd][1] == -1
			&& dup2(fd[lst->fd][0], lst->fd) == -1)
			NULL;
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
