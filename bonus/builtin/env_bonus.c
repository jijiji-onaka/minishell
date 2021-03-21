/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 17:18:21 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/17 04:40:23 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

static bool	env_len(char *s, size_t *len)
{
	bool	flag;

	*len = 0;
	flag = false;
	while (s[*len])
	{
		if (flag == false && s[*len] == '=')
			flag = true;
		(*len)++;
	}
	return (flag);
}

static void	display_env(t_minishell *info)
{
	t_envlst	*env;
	size_t		len;

	env = info->env;
	while (env)
	{
		if (env_len(env->value, &len) == true)
		{
			if (write(STDOUT_FILENO, env->value, len) < 0)
				all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
			if (write(STDOUT_FILENO, "\n", 1) < 0)
				all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
		}
		env = env->next;
	}
}

void		exec_env(t_minishell *info, t_cmdlst *cmd)
{
	char	*option;

	option = cmd->arg[1];
	if (option != NULL)
		return (error_mandatory(ERR_ENV, 37, info));
	display_env(info);
	g_signal.exit_status = 0;
}
