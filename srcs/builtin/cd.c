/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 01:13:20 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/08 08:00:37 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		set_oldpwd(t_minishell *info, char *oldpwd)
{
	char	*pwd_path;

	g_global.info.current_dir_path = info->current_dir_path;
	// g_global.info.oldpwd_path = info->current_dir_path;
	pwd_path = ft_getenv("PWD", info->env, false);
	if (pwd_path == NULL || pwd_path[0] == '\0')
	{
		update_env_value(&(info->env), "OLDPWD", "", info);
	}
	else if (oldpwd)
	{
		update_env_value(&(info->env), "OLDPWD", oldpwd, info);
	}
}

static void set_shell_path_flag(t_minishell *info)
{
	(void)info;
	if (g_global.info.unset_pwd_flag == true)
		g_global.info.unset_pwd_flag = false;
	if (g_global.info.unset_oldpwd_flag == true)
		g_global.info.unset_oldpwd_flag = false;
}

// bool	safe_opendir(DIR **dp, char *dir, t_minishell *info)
// {
// 	*dp = opendir(dir);
// 	if (*dp == NULL && errno == ENOENT)
// 		return (false);
// 	if (*dp == NULL)
// 		all_free_exit(info, ERR_OPENDIR, __LINE__, __FILE__);
// 	return (true);
// }

// bool		display_path_for_cd_path(t_minishell *info, char *dir)
// {
// 	DIR				*dp;
// 	struct dirent	*dirp;
// 	char			*cdpath;
// 	bool			ret;

// 	cdpath = ft_getenv("CDPATH", info->env, false);
// 	ret = false;
// 	if (cdpath == NULL)
// 		return (ret);
// 	if (safe_opendir(&dp, cdpath, info) == false)
// 		return (ret);
// 	while (1)
// 	{
// 		dirp = readdir(dp);
// 		if (dirp == NULL)
// 			break ;
// 		if (ft_strcmp(dirp->d_name, dir) == MATCH)
// 			ret = true;
// 	}
// 	if (errno != 0 && errno != ENOENT)
// 		all_free_exit(info, ERR_READDIR, __LINE__, __FILE__);
// 	if (closedir(dp) == -1)
// 		all_free_exit(info, ERR_CLOSEDIR, __LINE__, __FILE__);
// 	return (true);
// }

void		exec_cd(t_minishell *info, t_cmdlst *cmd)
{
	char	**arg;
	// bool	cd_path_flag;

	arg = cmd->arg;
	set_shell_path_flag(info);
	if (arg[1] == NULL ||
		(arg[1] != NULL && arg[1][0] == '~' && arg[1][1] == '\0'))
	{
		if (!(arg[1] = ft_getenv("HOME", info->env, false)))
			not_set_home_path(info);
		else
			go_to_path(info, &(arg[1]), false);
		arg[1] = NULL;
	}
	else if (arg[1][0] == '-' && arg[1][1] == '\0')
		go_to_oldpwd(info);
	else
		go_to_path(info, &(cmd->arg[1]), false);
	g_global.info.current_dir_path = info->current_dir_path;
	g_global.info.oldpwd_path = info->oldpwd_path;
}

/*
** else if (arg[1][0] == '-' && arg[1][1] == 'P' && arg[1][2] == '\0')
** go_to_path(info, &(cmd->arg[2]), true);
** else if (arg[1][0] == '-' && arg[1][1] == 'L' && arg[1][2] == '\0')
** go_to_path(info, &(cmd->arg[2]), false);
*/
