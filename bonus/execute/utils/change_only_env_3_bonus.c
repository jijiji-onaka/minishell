/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_only_env_3_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 23:41:22 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/13 14:03:24 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bonus_includes/minishell_bonus.h"

int	envval_len(char *str)
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
