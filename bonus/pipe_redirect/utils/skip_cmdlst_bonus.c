/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_cmdlst_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 12:41:51 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/13 14:03:24 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bonus_includes/minishell_bonus.h"

t_cmdlst	*skip_cmdlst(t_cmdlst **cmd_lst, size_t how_many, bool f)
{
	t_cmdlst	*next;
	size_t		i;

	i = 0;
	while (*cmd_lst && i < how_many)
	{
		next = (*cmd_lst)->next;
		if (f)
			free_alloc_ptr_in_cmd_lst(cmd_lst);
		*cmd_lst = next;
		i++;
	}
	return (*cmd_lst);
}
