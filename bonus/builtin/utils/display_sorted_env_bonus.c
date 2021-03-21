/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_sorted_env_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 01:04:08 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/18 00:21:55 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell_bonus.h"

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
			if (write(1, "\\", 1) < 0)
				all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
		if (write(1, str + i, 1) < 0)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
		i++;
	}
}

static void	print_env(char *value, t_minishell *info)
{
	size_t	i;
	size_t	j;
	int		flag;

	if ((flag = length_and_return_flag(value, &i, &j)) == 2)
		return ;
	if (write(1, "declare -x ", 11) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (flag == false)
	{
		if (ft_putendl_fd(value, 1) == false)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
		return ;
	}
	if (write(1, value, j + 1) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (write(1, "\"", 1) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	put_env_value(value + j + 1, info);
	if (write(1, "\"\n", 2) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
}

void		display_sorted_env(t_minishell *info)
{
	t_envlst	*tmp;
	t_envlst	*sort_env;

	if (!(sort_env = dup_merge_lst_sort(info->env)))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	while (sort_env)
	{
		tmp = sort_env->next;
		print_env(sort_env->value, info);
		free(sort_env);
		sort_env = tmp;
	}
	sort_env = NULL;
}
