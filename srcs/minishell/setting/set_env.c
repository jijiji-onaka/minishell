/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 01:58:39 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/16 12:55:49 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static t_envlst	*make_env(char *env, t_minishell *info, int f)
{
	t_envlst	*new;

	if (ft_strncmp("OLDPWD", env, 6) == 0 && f)
		return (NULL);
	if (!(new = malloc(sizeof(t_envlst))))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	if (!(new->value = ft_strdup(env)))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	new->next = NULL;
	new->qnext = NULL;
	return (new);
}

void			set_env(t_minishell *info)
{
	t_envlst	*begin;
	t_envlst	*next;
	size_t		i;
	extern char	**environ;

	begin = make_env(environ[0], info, 1);
	info->env = begin;
	i = 0;
	while (environ[++i])
	{
		if (!(next = make_env(environ[i], info, 1)))
			continue ;
		begin->next = next;
		begin = next;
	}
	next = make_env("OLDPWD", info, 0);
	begin->next = next;
	begin = next;
}
