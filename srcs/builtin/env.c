/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 17:18:21 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 17:03:49 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	display_env(t_minishell_info *info)
{
	t_envlst	*env;

	env = info->env;
	while (env)
	{
		if (printf("%s\n", env->value) == -1)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
		env = env->next;
	}
}

void		exec_env(t_minishell_info *info, char *arg)
{
	if (arg != NULL)
		return (error_mandatory(ERR_ENV, 37, info));
	display_env(info);
}
