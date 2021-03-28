/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_index_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 21:14:10 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/24 00:36:27 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell_bonus.h"

int	return_index(int type)
{
	if (type == BIN)
		return (0);
	else if (type == EXIT)
		return (1);
	else if (type == PWD)
		return (2);
	else if (type == CMD_ECHO)
		return (3);
	else if (type == CD)
		return (4);
	else if (type == ENV)
		return (5);
	else if (type == EXPORT)
		return (6);
	else if (type == UNSET)
		return (7);
	return (END_OF_THE_WORLD);
}
