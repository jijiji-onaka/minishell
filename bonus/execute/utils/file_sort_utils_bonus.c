/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_sort_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 14:47:21 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/13 14:48:37 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bonus_includes/minishell_bonus.h"

void	*destroy_queue_(t_wild_lst **qhead)
{
	t_wild_lst	*tmp;
	t_wild_lst	*begin;

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
