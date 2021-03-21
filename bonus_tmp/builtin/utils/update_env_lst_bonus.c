/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 16:37:31 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/17 04:37:54 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell_bonus.h"

static t_envlst	*make_env(char *env_name, char *env_value,
					t_minishell *info)
{
	t_envlst	*new;

	if (!(new = malloc(sizeof(t_envlst))))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	if (env_value == NULL)
		new->value = env_name;
	else if (!(new->value = ft_str3join(env_name, "=", env_value)))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	new->next = NULL;
	new->qnext = NULL;
	return (new);
}

void			update_env_lst(t_envlst **env, char *env_name, char *env_value,
							t_minishell *info)
{
	t_envlst	*begin;
	t_envlst	*save;

	begin = *env;
	while (*env)
	{
		if ((*env)->value[0] == env_name[0] &&
			ft_strncmp(env_name, (*env)->value, ft_strlen(env_name)) == 0)
		{
			if (env_value == NULL)
				(*env)->value = env_name;
			else if (!((*env)->value =
					re_str3join(&((*env)->value), env_name, "=", env_value)))
				all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
			*env = begin;
			return ;
		}
		if ((*env)->next == NULL)
			save = *env;
		*env = (*env)->next;
	}
	save->next = make_env(env_name, env_value, info);
	info->env = begin;
}
