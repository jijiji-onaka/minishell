/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 01:58:39 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/28 05:27:13 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void		set_info_environ(char **environ, size_t i, bool flag,
				t_minishell_info *info)
{
	if (!(info->environ = malloc(sizeof(char *) *
				(i + 1 + (flag == 0 ? 1 : 0)))))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	i = 0;
	while (environ[i])
	{
		info->environ[i] = environ[i];
		i++;
	}
	if (flag == 0)
		info->environ[i++] = "OLDPWD";
	info->environ[i] = NULL;
}

static t_envlst	*make_env(char *env, t_minishell_info *info)
{
	t_envlst	*new;

	if (!(new = malloc(sizeof(t_envlst))))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	if (!(new->value = ft_strdup(env)))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	new->next = NULL;
	return (new);
}

void			set_env(t_minishell_info *info)
{
	t_envlst	*begin;
	t_envlst	*next;
	size_t		i;
	bool		flag;
	extern char	**environ;

	begin = make_env(environ[0], info);
	info->env = begin;
	i = 0;
	flag = false;
	while (environ[++i])
	{
		if ((environ[i][0] == 'O' && environ[i][1] == 'L' &&
			environ[i][2] == 'D' && ft_strncmp(environ[i] + 3, "PWD", 3) == 0))
			flag = true;
		next = make_env(environ[i], info);
		begin->next = next;
		begin = next;
	}
	set_info_environ(environ, i, flag, info);
}
