/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 01:58:39 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/13 14:03:24 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bonus_includes/minishell_bonus.h"

static t_string	make_key(char *src, t_minishell *info)
{
	t_string	res;

	if (src == NULL)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	res.str = src;
	res.len = ft_strlen(src);
	return (res);
}

static t_string	make_value(char *src, bool is_val, t_minishell *info)
{
	t_string	res;

	if (is_val)
	{
		res.str = NULL;
		res.len = 0;
		return (res);
	}
	res.str = ft_strdup(src);
	if (res.str == NULL)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	res.len = ft_strlen(src);
	return (res);
}

static t_envlst	*initial_make_struct_env(char *env, t_minishell *info)
{
	t_envlst	*new;
	char		*equ_ptr;
	size_t		key_len;

	new = malloc(sizeof(t_envlst));
	if (new == NULL)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	equ_ptr = ft_strchr(env, '=');
	if (equ_ptr == NULL)
		key_len = -1;
	else
		key_len = equ_ptr - env;
	new->env.key = make_key(ft_substr(env, 0, key_len), info);
	new->env.value = make_value(env + key_len + 1, equ_ptr == NULL, info);
	new->next = NULL;
	new->qnext = NULL;
	return (new);
}

void	set_env(t_minishell *info)
{
	t_envlst	*begin;
	t_envlst	*next;
	size_t		i;
	extern char	**environ;

	i = 0;
	if (ft_strncmp("OLDPWD", environ[0], 6) == MATCH)
	{
		begin = initial_make_struct_env(environ[1], info);
		i = 1;
	}
	else
		begin = initial_make_struct_env(environ[0], info);
	info->env = begin;
	while (environ[++i])
	{
		if (ft_strncmp("OLDPWD", environ[i], 6) == MATCH)
			continue ;
		next = initial_make_struct_env(environ[i], info);
		begin->next = next;
		begin = next;
	}
	next = initial_make_struct_env("OLDPWD", info);
	begin->next = next;
	begin = next;
}
