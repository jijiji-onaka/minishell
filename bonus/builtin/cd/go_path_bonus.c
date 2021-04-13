/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_go_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 17:43:47 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/10 12:24:27 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bonus_includes/minishell_bonus.h"

static void	when_double_slash_root(char *dir, t_minishell *info)
{
	int		comp[4];

	comp[0] = !ft_strncmp("/", dir, 1);
	comp[1] = !ft_strncmp("//", dir, 2);
	comp[2] = !ft_strncmp("///", dir, 3);
	comp[3] = !ft_strncmp("//", info->current_dir_path, 2);
	if ((comp[1] || comp[3]) && !comp[2] && comp[0])
	{
		info->current_dir_path = re_strjoin(&(info->current_dir_path),
				"/", info->current_dir_path);
		if (info->current_dir_path == NULL)
			all_free_exit(info, ERR_GETCWD, __LINE__, __FILE__);
	}
}

static bool	ch_each_path(t_minishell *info, char *dir)
{
	int		i;
	char	**split;
	char	*new;

	i = -1;
	split = ft_split(dir, '/');
	if (split == NULL)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	while (split[++i])
	{
		new = getcwd(NULL, 0);
		if (new == NULL)
			return (not_found_cwd(info, dir, &split));
		else if (ft_strcmp(split[i], ".") == 0)
			go_cwd(info, info->current_dir_path, dir);
		else if (ft_strcmp(split[i], "..") == 0)
			go_to_upper_dir(info->current_dir_path, info);
		else
			connect_path(&(info->current_dir_path), split[i], info);
		free(new);
	}
	ptr_2d_free((void ***)&(split), -1);
	return (true);
}

static bool	change_root_dir(t_minishell *info, bool absolute_path)
{
	if (absolute_path)
	{
		if (safe_chdir("/", NULL, info) == false)
			return (false);
		info->current_dir_path = re_strdup(&(info->current_dir_path), "/");
	}
	return (true);
}

static bool	change_dir(char *dir, t_minishell *info)
{
	char	*oldpwd;

	oldpwd = ft_strdup(ft_getenv("PWD", info->env, false));
	if (oldpwd == NULL)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	if (change_root_dir(info, dir[0] == '/') == false)
	{
		ptr_free((void **)&oldpwd);
		return (false);
	}
	if (ch_each_path(info, dir) == false)
	{
		ptr_free((void **)&oldpwd);
		return (false);
	}
	set_oldpwd(info, oldpwd);
	info->oldpwd_path = re_strdup(&(info->oldpwd_path), oldpwd);
	ptr_free((void **)&oldpwd);
	return (true);
}

void	go_path(t_minishell *info, char **dir)
{
	bool	cd_path_flag;

	cd_path_flag = is_cdpath(info, dir);
	if (safe_chdir(*dir, NULL, info) == false)
		return ;
	info->oldpwd_path = re_strdup(&(info->oldpwd_path), info->current_dir_path);
	if (change_dir(*dir, info) == false)
		return ;
	when_double_slash_root(*dir, info);
	update_env_value(&(info->env), "PWD", info->current_dir_path, info);
	if (cd_path_flag)
		ft_putendl_fd(info->current_dir_path, STDOUT);
	g_global.exit_status = 0;
}
