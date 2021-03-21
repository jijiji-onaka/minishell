/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 01:13:20 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/21 14:50:57 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		set_oldpwd(t_minishell *info, char *oldpwd)
{
	char	*pwd_path;
	bool	flag;

	g_signal.info.current_dir_path = info->current_dir_path;
	g_signal.info.oldpwd_path = info->oldpwd_path;
	pwd_path = search_env("PWD", 3, info->env, &flag);
	if (pwd_path == NULL || pwd_path[0] == '\0' || flag == false)
		update_env_lst(&(info->env), "OLDPWD", "", info);
	else if (oldpwd)
		update_env_lst(&(info->env), "OLDPWD", oldpwd, info);
}

void		exec_cd(t_minishell *info, t_cmdlst *cmd)
{
	char	**arg;

	arg = cmd->arg;
	if (arg[1] == NULL ||
		(arg[1] != NULL && arg[1][0] == '~' && arg[1][1] == '\0'))
	{
		if (!(arg[1] = search_env("HOME", 4, info->env, NULL)))
			return (not_set_home_path(info));
		go_to_path(info, &(arg[1]), false);
		arg[1] = NULL;
	}
	else if (arg[1][0] == '-' && arg[1][1] == '\0')
		go_to_oldpwd(info);
	else
		go_to_path(info, &(cmd->arg[1]), false);
}

/*
** else if (arg[1][0] == '-' && arg[1][1] == 'P' && arg[1][2] == '\0')
** go_to_path(info, &(cmd->arg[2]), true);
** else if (arg[1][0] == '-' && arg[1][1] == 'L' && arg[1][2] == '\0')
** go_to_path(info, &(cmd->arg[2]), false);
*/
