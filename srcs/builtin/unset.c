/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 18:44:56 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 17:04:13 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	remove_env_lst_if(t_envlst **env, char *data, int (*cmp_by)())
{
	t_envlst	*begin;
	t_envlst	*remove;

	begin = *env;
	while (*env && (*env)->next)
	{
		if (cmp_by(data, (*env)->next->value, ft_strlen(data)) == 0)
		{
			remove = (*env)->next;
			(*env)->next = (*env)->next->next;
			ptr_free((void **)&(remove->value));
			ptr_free((void **)&remove);
		}
		*env = (*env)->next;
	}
	*env = begin;
	if (cmp_by(data, (*env)->value, ft_strlen(data)) == 0)
	{
		remove = (*env)->next;
		(*env)->next = (*env)->next->next;
		ptr_free((void **)&(remove->value));
		ptr_free((void **)remove);
	}
}

void		exec_unset(t_minishell_info *info, char **args)
{
	int	i;

	if (args[1][0] == '-')
		return (error_mandatory(ERR_UNSET, 29, info));
	i = 0;
	while (args[i])
	{
		remove_env_lst_if(&(info->env), args[i], ft_strncmp);
		i++;
	}
}
