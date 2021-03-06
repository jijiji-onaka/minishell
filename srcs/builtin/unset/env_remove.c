/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_remove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 17:55:27 by tjinichi          #+#    #+#             */
/*   Updated: 2021/05/13 01:16:31 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	free_env(t_env env)
{
	if (env.key.str)
		ptr_free((void **)&(env.key.str));
	if (env.value.str)
		ptr_free((void **)&(env.value.str));
}

void	remove_env_lst_if(t_envlst **env, char *data)
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
			free_env(remove->env);
			free(remove);
		}
		else
			*env = (*env)->next;
	}
	*env = begin;
	if (ft_strcmp((*env)->env.key.str, data) == MATCH)
	{
		begin = (*env)->next;
		free_env((*env)->env);
		free(*env);
		*env = begin;
		g_global.info.env = *env;
	}
}
