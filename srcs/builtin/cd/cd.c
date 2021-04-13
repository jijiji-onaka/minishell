/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 01:13:20 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/10 13:04:07 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	set_shell_path_flag(t_minishell *info)
{
	(void)info;
	if (g_global.info.unset_pwd_flag == true)
		g_global.info.unset_pwd_flag = false;
	if (g_global.info.unset_oldpwd_flag == true)
		g_global.info.unset_oldpwd_flag = false;
}

void	exec_cd(t_minishell *info, t_cmdlst *cmd)
{
	char	**arg;

	arg = cmd->arg;
	set_shell_path_flag(info);
	if (arg[1] == NULL
		|| (arg[1] != NULL && arg[1][0] == '~' && arg[1][1] == '\0'))
	{
		arg[1] = ft_getenv("HOME", info->env, false);
		if (arg[1] == NULL)
			not_set_home_path(info);
		else
			go_path(info, &(arg[1]));
		arg[1] = NULL;
	}
	else if (arg[1][0] == '-' && arg[1][1] == '\0')
		go_oldpwd(info);
	else
		go_path(info, &(cmd->arg[1]));
	g_global.info.current_dir_path = info->current_dir_path;
	g_global.info.oldpwd_path = info->oldpwd_path;
}
