/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 18:44:56 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/04 02:04:40 by tjinichi         ###   ########.fr       */
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
		else
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
	int		i;
	char	*tmp;

	if (args[1][0] == '-')
		return (error_mandatory(ERR_UNSET, 29, info));
	i = 0;
	while (args[i])
	{
		if (args[i][0] == '\'' || args[i][0] == '\"')
			if (!(args[i] = re_strtrim(&(args[i]), "\'\"")))
				all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
		if (args[i][0] == '$')
			tmp = search_env(args[i] + 1, ft_strlen(args[i] + 1), info->env);
		else
			tmp = args[i];
		remove_env_lst_if(&(info->env), tmp, ft_strncmp);
		i++;
	}
}
