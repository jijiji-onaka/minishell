/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 17:18:21 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/04 03:01:19 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	display_env(t_minishell *info)
{
	t_envlst	*lst;

	lst = info->env;
	while (lst)
	{
		if (lst->env.value.str != NULL)
		{
			if (write(STDOUT, lst->env.key.str,
						lst->env.key.len) < 0)
				all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
			if (write(STDOUT, "=", 1) < 0)
				all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
			if (write(STDOUT, lst->env.value.str,
						lst->env.value.len) < 0)
				all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
			if (write(STDOUT, "\n", 1) < 0)
				all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
		}
		lst = lst->next;
	}
}

void		exec_env(t_minishell *info, t_cmdlst *cmd)
{
	char	*option;

	option = cmd->arg[1];
	if (option != NULL)
		return (error_mandatory(ERR_ENV, 37, info));
	display_env(info);
	g_global.exit_status = 0;
}
