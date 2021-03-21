/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 14:18:58 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/21 14:22:22 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char		**get_path(t_envlst *lst, t_minishell *info)
{
	int			len;
	t_envlst	*begin;
	char		**tmp;

	len = 0;
	begin = lst;
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	if (!(tmp = malloc(sizeof(char *) * (len + 1))))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	lst = begin;
	len = 0;
	while (lst)
	{
		tmp[len++] = lst->value;
		lst = lst->next;
	}
	tmp[len] = NULL;
	return (tmp);
}
