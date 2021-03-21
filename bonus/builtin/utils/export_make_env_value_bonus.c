/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_make_env_value.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 20:41:03 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/17 04:37:54 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell_bonus.h"

char		*make_env_value(char *arg, t_minishell *info, char **ptr)
{
	int		i;
	char	*res;

	i = -1;
	while (arg[++i])
		;
	if (!(res = malloc(sizeof(char) * (i + 1))))
	{
		ptr_free((void**)ptr);
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	}
	i = 0;
	while (*arg)
	{
		res[i++] = *arg;
		arg++;
	}
	res[i] = '\0';
	return (res);
}

char		*add_env_value(char *arg, t_minishell *info, char **env_name)
{
	char	*search;
	char	*res;

	search = search_env(*env_name, ft_strlen(*env_name), info->env);
	if (search == NULL)
		return (make_env_value(arg, info, env_name));
	else
	{
		if (!(res = ft_strjoin(search, arg)))
		{
			ptr_free((void**)env_name);
			all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
		}
	}
	return (res);
}
