/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 11:49:32 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/10 11:52:01 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	dup_pos(int dst[2], int src[2])
{
	dst[X] = src[X];
	dst[Y] = src[Y];
}

bool	equal_pos(int cmp_1[2], int cmp_2[2])
{
	if (cmp_1 == NULL || cmp_2 == NULL)
		return (false);
	if (cmp_1[X] - cmp_2[X] != 0)
		return (false);
	if (cmp_1[Y] - cmp_2[Y] != 0)
		return (false);
	return (true);
}
