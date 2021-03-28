/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_remove_env_lst_if.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 17:55:27 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/25 00:16:40 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	compare(char *s1, char *s2, size_t n)
{
	size_t			i;
	unsigned char	*u_s1;
	unsigned char	*u_s2;

	if (!s1 || !s2)
		return (INT_MIN);
	i = 0;
	u_s1 = (unsigned char *)s1;
	u_s2 = (unsigned char *)s2;
	while (i < n)
	{
		if (u_s1[i] == '\0' || u_s1[i] != u_s2[i])
			return (u_s1[i] - u_s2[i]);
		i++;
	}
	if (s1[i] != '=' && s1[i] != '\0')
		return (-1);
	return (0);
}

void		remove_env_lst_if(t_envlst **env, char *data)
{
	t_envlst	*begin;
	t_envlst	*remove;

	begin = *env;
	while (*env && (*env)->next)
	{
		if (ft_strcmp((*env)->next->env.key.str, data) == MATCH)
		{
			remove = (*env)->next;
			(*env)->next = (*env)->next->next;
			ptr_free((void **)&(remove->env.key.str));
			ptr_free((void **)&(remove->env.value.str));
			free(remove);
		}
		else
			*env = (*env)->next;
	}
	*env = begin;
	if (ft_strcmp((*env)->env.key.str, data) == MATCH)
	{
		begin = (*env)->next;
		ptr_free((void **)&((*env)->env.key.str));
		ptr_free((void **)&((*env)->env.value.str));
		free(*env);
		*env = begin;
		g_global.info.env = *env;
	}
}
