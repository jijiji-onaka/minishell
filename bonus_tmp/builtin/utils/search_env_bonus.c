/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_env_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 19:18:45 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/21 16:54:43 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell_bonus.h"

static int	compare(char *s1, char *s2, size_t n, bool *flag)
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
		if ((u_s1[i] == '\0') || u_s1[i] != u_s2[i])
			return (u_s1[i] - u_s2[i]);
		i++;
	}
	if (u_s1[i] == '\0' && flag)
		*flag = true;
	else if (u_s1[i] != '=' || (u_s2[i] != '\0' && u_s2[i] != ' '
	&& u_s2[i] != '$' && u_s2[i] != '\"' && u_s2[i] != '\'' && u_s2[i] != '\\'
	&& u_s2[i] != '-' && u_s2[i] != '.' && u_s2[i] != '/'
	&& ft_isdigit(u_s2[i])))
		return (-1);
	return (0);
}

char		*search_env(char *str, int num, t_envlst *env_lst, bool *flag)
{
	size_t		i;

	if (flag)
		*flag = true;
	while (env_lst)
	{
		if ((env_lst->value)[0] == str[0] &&
				compare(env_lst->value, str, num, flag) == 0)
		{
			i = 0;
			while (env_lst->value[i] && env_lst->value[i] != '=')
				i++;
			return (env_lst->value + i + 1);
		}
		env_lst = env_lst->next;
	}
	if (flag)
		*flag = false;
	if ('P' == str[0] && ft_strcmp("PWD", str) == 0)
		return (g_signal.info.current_dir_path);
	return (NULL);
}
