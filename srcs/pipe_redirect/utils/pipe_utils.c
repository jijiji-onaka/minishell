/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 18:09:44 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/11 13:31:59 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool	is_now_middle_pipe(t_cmdlst *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		if (lst->type == PIPE)
			i++;
		else if (lst->type == SEMICOLON)
			return (false);
		lst = lst->next;
		if (i == 2)
			return (true);
	}
	return (false);
}

void	skip_command(t_cmdlst **cmd_lst)
{
	if ((*cmd_lst && is_redir((*cmd_lst)->type)))
		while ((*cmd_lst && is_redir((*cmd_lst)->type)))
			*cmd_lst = (*cmd_lst)->next->next;
	else
	{
		while ((*cmd_lst && (*cmd_lst)->next
				&& is_redir((*cmd_lst)->next->type)))
			*cmd_lst = (*cmd_lst)->next->next;
		*cmd_lst = (*cmd_lst)->next;
	}
}

t_cmdlst	*get_next_command(t_cmdlst *lst)
{
	while (lst)
	{
		if (lst->type != SEMICOLON && lst->type != PIPE)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
