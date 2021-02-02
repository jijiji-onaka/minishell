/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_lst_and_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 22:39:58 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 17:37:36 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_cmdlst	*skip_lst_and_free(t_cmdlst **cmd_lst, int how_many)
{
	t_cmdlst	*next;
	int			i;

	i = 0;
	while (*cmd_lst && i < how_many)
	{
		next = (*cmd_lst)->next;
		free_alloc_ptr_in_cmd_lst(cmd_lst);
		*cmd_lst = next;
		i++;
	}
	return (*cmd_lst);
}
