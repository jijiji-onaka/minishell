/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_environ_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 14:18:58 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/21 21:03:45 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell_bonus.h"

static int	envlst_size(t_envlst *lst)
{
	int	len;

	len = 0;
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}

char		**get_environ(t_envlst *lst, t_minishell *info)
{
	char	**res;
	int		i;

	res = malloc(sizeof(char *) * (envlst_size(lst) + 1));
	if (res == NULL)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	i = 0;
	while (lst)
	{
		if (lst->env.value.str)
			res[i++] = ft_str3join(lst->env.key.str, "=", lst->env.value.str);
		else
			res[i++] = ft_strdup(lst->env.key.str);
		if (res[i - 1] == NULL)
		{
			ptr_2d_free((void***)&res, -1);
			all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
		}
		lst = lst->next;
	}
	res[i] = NULL;
	return (res);
}
