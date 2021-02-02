/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 01:13:20 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 20:52:27 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	go_to_home(t_minishell_info *info)
{
	char		*home_path;

	update_env_lst(&(info->env), "OLDPWD=", info->current_dir_path, info);
	home_path = search_env("HOME", 4, info->env);
	if (chdir(home_path) == -1)
		all_free_exit(info, ERR_CHDIR, __LINE__, __FILE__);
	ptr_free((void **)&(info->current_dir_path));
	info->current_dir_path = home_path;
}

static void	go_to_path(t_minishell_info *info, char *dir,
			bool option_p_flag)
{
	char		*dir_name;

	if (dir == NULL)
		return (go_to_home(info));
	if (dir[0] == '.' && dir[1] == '\0')
		return ;
	update_env_lst(&(info->env), "OLDPWD=", info->current_dir_path, info);
	dir_name = dir;
	if (dir[0] == '$' && dir[1] != '\0')
		dir_name = search_env(dir + 1, ft_strlen(dir + 1), info->env);
	if (option_p_flag == false)
		if (is_symbolic_dir(info, dir_name) == true)
			return ;
	if (chdir(dir_name) == -1)
	{
		if (errno == EFAULT || errno == EIO || errno == ENOMEM)
			all_free_exit(info, ERR_CHDIR, __LINE__, __FILE__);
		if (write(STDERR_FILENO, "minishell: ", 12) < 0)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
		perror(dir_name);
	}
	ptr_free((void **)&(info->current_dir_path));
	info->current_dir_path = getcwd(NULL, 0);
	update_env_lst(&(info->env), "PWD=", info->current_dir_path, info);
}

static void	go_to_oldpwd(t_minishell_info *info)
{
	char		*oldpwd_path;

	oldpwd_path = search_env("OLDPWD", 6, info->env);
	if (oldpwd_path == NULL)
	{
		if (write(STDERR_FILENO, NO_OLDPWD, 29) < 0)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
		return ;
	}
	if (chdir(oldpwd_path) == -1)
		all_free_exit(info, ERR_CHDIR, __LINE__, __FILE__);
	if (ft_putendl_fd(oldpwd_path, 1) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	update_env_lst(&(info->env), "OLDPWD=", info->current_dir_path, info);
	ptr_free((void **)&(info->current_dir_path));
	info->current_dir_path = oldpwd_path;
}

void		exec_cd(t_minishell_info *info, t_cmdlst *cmd)
{
	char	**arg;

	arg = cmd->arg;
	if (arg[1] == NULL ||
		(arg[1] != NULL && arg[1][0] == '~' && arg[1][1] == '\0'))
		go_to_home(info);
	if (arg[1][0] == '-' && arg[1][1] == '\0')
		go_to_oldpwd(info);
	else if (arg[1][0] == '-' && arg[1][1] == 'P' && arg[1][2] == '\0')
		go_to_path(info, arg[2], true);
	else if (arg[1][0] == '-' && arg[1][1] == 'L' && arg[1][2] == '\0')
		go_to_path(info, arg[2], false);
	else
		go_to_path(info, arg[1], false);
	g_working_dir = info->current_dir_path;
}
