/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 16:37:31 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/10 13:57:22 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static t_envlst	*make_env(t_string key, t_string value,
					t_minishell *info)
{
	t_envlst	*new;

	new = malloc(sizeof(t_envlst));
	if (new == NULL)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	new->env.value = value;
	new->env.key = key;
	new->next = NULL;
	new->qnext = NULL;
	return (new);
}

static bool	shell_val_to_env_val(char *key, t_string *value, t_minishell *info)
{
	int		flag;
	char	*str;

	flag = 42;
	if (ft_strcmp(key, "PWD") == MATCH)
		flag = PWD;
	else if (ft_strcmp(key, "OLDPWD") == MATCH)
		flag = OLDPWD;
	if (flag == 42 || value->str != NULL)
		return (false);
	if (flag == PWD)
		str = info->current_dir_path;
	else
		str = info->oldpwd_path;
	value->str = ft_strdup(str);
	if (value->str == NULL)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	value->len = ft_strlen(str);
	return (true);
}

static void	re_assign(t_string *dst, t_string src)
{
	ptr_free((void **)&(dst->str));
	*dst = src;
}

void	update_env_lst(t_envlst **env, t_string key, t_string value,
							t_minishell *info)
{
	t_envlst	*begin;
	t_envlst	*save;

	begin = *env;
	while (*env)
	{
		if (equal(ft_strcmp(key.str, (*env)->env.key.str)))
		{
			if (value.str && (*env)->env.value.str == NULL)
				(*env)->env.value = value;
			else if (value.str)
				re_assign(&((*env)->env.value), value);
			ptr_free((void **)&(key.str));
			*env = begin;
			return ;
		}
		if ((*env)->next == NULL)
			save = *env;
		*env = (*env)->next;
	}
	shell_val_to_env_val(key.str, &value, info);
	save->next = make_env(key, value, info);
	info->env = begin;
}

void	update_env_value(t_envlst **env, char *key, char *value,
							t_minishell *info)
{
	t_envlst	*begin;

	begin = *env;
	while (*env)
	{
		if (ft_strcmp(key, (*env)->env.key.str) == MATCH)
		{
			(*env)->env.value.str = re_strdup(&((*env)->env.value.str), value);
			if ((*env)->env.value.str == NULL)
				all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
			(*env)->env.value.len = ft_strlen((*env)->env.value.str);
			*env = begin;
			return ;
		}
		*env = (*env)->next;
	}
	info->env = begin;
}
