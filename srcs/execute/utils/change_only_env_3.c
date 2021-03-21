/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_only_env_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 23:41:22 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/19 15:12:30 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int			envval_len(char *str)
{
	int	len;

	len = 0;
	while (*str)
	{
		if (is_quo(*str) || *str == '$')
			len += 2;
		len++;
		(str)++;
	}
	return (len);
}
