/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 19:18:45 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 16:59:56 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*search_env(char *str, int num, t_envlst *env_lst)
{
	size_t		i;

	while (env_lst)
	{
		if ((env_lst->value)[0] == str[0] &&
				ft_strncmp(env_lst->value, str, num) == 0)
		{
			i = 0;
			while (env_lst->value[i] != '=')
				i++;
			return (env_lst->value + i + 1);
		}
		env_lst = env_lst->next;
	}
	return (NULL);
}
