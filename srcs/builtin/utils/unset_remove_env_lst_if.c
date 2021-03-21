/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_remove_env_lst_if.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 17:55:27 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/21 14:36:34 by tjinichi         ###   ########.fr       */
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
		if (compare((*env)->next->value, data, ft_strlen(data)) == 0)
		{
			remove = (*env)->next;
			(*env)->next = (*env)->next->next;
			ptr_free((void **)&(remove->value));
			free(remove);
		}
		else
			*env = (*env)->next;
	}
	*env = begin;
	if (compare((*env)->value, data, ft_strlen(data)) == 0)
	{
		begin = (*env)->next;
		ptr_free((void **)&((*env)->value));
		free(*env);
		*env = begin;
		g_signal.info.env = *env;
	}
}
