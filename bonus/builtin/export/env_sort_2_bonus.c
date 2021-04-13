/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sort_2_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 00:32:20 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/13 14:03:24 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bonus_includes/minishell_bonus.h"

void	*destroy_queue(t_envlst **qhead)
{
	t_envlst	*tmp;
	t_envlst	*begin;

	begin = *qhead;
	while (*qhead)
	{
		tmp = (*qhead)->qnext;
		free(*qhead);
		*qhead = tmp;
	}
	*qhead = begin;
	*qhead = NULL;
	return (NULL);
}
