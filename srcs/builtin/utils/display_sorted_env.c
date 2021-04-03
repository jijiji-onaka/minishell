/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_sorted_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 01:04:08 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/04 03:01:19 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	length_and_return_flag(char *value, size_t *i, size_t *j)
{
	int		flag;

	if (value[0] == '_' && value[1] == '=')
		return (2);
	*i = 0;
	flag = false;
	while (value[*i])
	{
		if (flag == false && value[*i] == '=')
		{
			flag = true;
			*j = *i;
		}
		(*i)++;
	}
	return (flag);
}

static void	put_env_value(char *str, t_minishell *info)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\\' || str[i] == '$' || str[i] == '`')
			if (write(STDOUT, "\\", 1) < 0)
				all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
		if (write(STDOUT, str + i, 1) < 0)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
		i++;
	}
}

static void	display_env(t_env env, t_minishell *info)
{
	size_t	i;
	size_t	j;

	if (write(STDOUT, "declare -x ", 11) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (env.key.str && env.value.str == NULL)
	{
		if (write(STDOUT, env.key.str, env.key.len) < 0)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
		if (write(STDOUT, "\n", 1) < 0)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
		return ;
	}
	if (write(STDOUT, env.key.str, env.key.len) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (write(STDOUT, "=\"", 2) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	put_env_value(env.value.str, info);
	if (write(STDOUT, "\"\n", 2) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
}

void		display_sorted_env(t_minishell *info)
{
	t_envlst	*tmp;
	t_envlst	*sort_env;

	if (!(sort_env = merge_lst_sort(info->env)))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	while (sort_env)
	{
		tmp = sort_env->next;
		display_env(sort_env->env, info);
		free(sort_env);
		sort_env = tmp;
	}
	sort_env = NULL;
}
