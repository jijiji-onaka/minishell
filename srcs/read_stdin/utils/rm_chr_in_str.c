/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_chr_in_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 16:17:05 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 17:26:29 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	rm_chr_in_str(char **str, char chr)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while ((*str)[i])
	{
		if ((*str)[i] != chr)
		{
			(*str)[j] = (*str)[i];
			j++;
		}
		i++;
	}
	(*str)[j] = '\0';
}
