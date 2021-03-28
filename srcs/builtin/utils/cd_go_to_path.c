/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_go_to_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 17:43:47 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/25 22:06:59 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	when_double_slash_root(char *dir, t_minishell *info)
{
	int		comp[4];

	comp[0] = !ft_strncmp("/", dir, 1);
	comp[1] = !ft_strncmp("//", dir, 2);
	comp[2] = !ft_strncmp("///", dir, 3);
	comp[3] = !ft_strncmp("//", info->current_dir_path, 2);
	if ((comp[1] || comp[3]) && !comp[2] && comp[0])
	{
		if (!(info->current_dir_path = re_strjoin(&(info->current_dir_path)
		, "/", info->current_dir_path)))
			all_free_exit(info, ERR_GETCWD, __LINE__, __FILE__);
	}
}

static bool	ch_each_path(t_minishell *info, char *dir)
{
	int		i;
	char	**split;
	char	*new;

	i = -1;
	if (!(split = ft_split(dir, '/')))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	while (split[++i])
	{
		if (!(new = getcwd(NULL, 0)))
			return (not_found_cwd(info, dir, &split));
		else if (ft_strcmp(split[i], ".") == 0)
			go_to_cwd(info, info->current_dir_path, dir);
		else if (ft_strcmp(split[i], "..") == 0)
			go_to_upper_dir(info->current_dir_path, info);
		else
			connect_path(&(info->current_dir_path), split[i], info);
		free(new);
	}
	ptr_2d_free((void***)&(split), -1);
	info->ptr_2d_for_free = NULL;
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
	bool	flag;

	if (!(oldpwd = ft_strdup(ft_getenv("PWD", info->env, false))))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	if (change_root_dir(info, dir[0] == '/') == false)
	{
		ptr_free((void**)&oldpwd);
		return (false);
	}
	if (ch_each_path(info, dir) == false)
	{
		ptr_free((void**)&oldpwd);
		return (false);
	}
	flag = false;
	set_oldpwd(info, oldpwd);
	info->oldpwd_path = re_strdup(&(info->oldpwd_path), oldpwd);
	ptr_free((void**)&oldpwd);
	return (true);
}




bool	safe_opendir(DIR **dp, char *dir, t_minishell *info)
{
	*dp = opendir(dir);
	if (*dp == NULL && errno == ENOENT)
		return (false);
	if (*dp == NULL)
		all_free_exit(info, ERR_OPENDIR, __LINE__, __FILE__);
	return (true);
}

bool	safe_readdir(t_dirent **dirp, DIR *dp, t_minishell *info)
{
	*dirp = readdir(dp);
	if (*dirp != NULL)
		return (true);
	// if (errno != 0 && errno != ENOENT)
	// 	all_free_exit(info, ERR_READDIR, __LINE__, __FILE__);
	return (false);
}

void	safe_closedir(DIR **dp, t_minishell *info)
{
	if (closedir(*dp) == -1)
		all_free_exit(info, ERR_CLOSEDIR, __LINE__, __FILE__);
}

bool		get_path(char **split, char **dir, t_minishell *info)
{
	int			i;
	DIR			*dp;
	t_dirent	*dirp;
	bool		ret;

	i = -1;
	ret = false;
	while (split[++i] && ret == false)
	{
		if (safe_opendir(&dp, split[i], info) == false)
			return (false);
		while (ret == false)
		{
			if (safe_readdir(&dirp, dp, info) == false)
				break ;
			if (dirp->d_name[0] == '.')
				continue ;
			if (equal(ft_strcmp(dirp->d_name, *dir)))
			{
				connect_path(&(split[i]), dirp->d_name, info);
				int fd = open(split[i], O_RDONLY);
				if (fd == -1)
					continue ;
				close(fd);
				*dir = re_strdup(dir, split[i]);
				safe_closedir(&dp, info);
				return (true);
			}
		}
		safe_closedir(&dp, info);
	}
	return (ret);
}

bool		is_cd_path(t_minishell *info, char **dir)
{
	char		*cdpath;
	char		**split;
	bool		ret;
	bool		srcdir_absolute_flag;

	srcdir_absolute_flag = false;
	if ((*dir)[0] == '/')
		srcdir_absolute_flag = true;
	cdpath = ft_getenv("CDPATH", info->env, false);
	if (cdpath == NULL || cdpath[0] == ':')
		return (false);
	split = ft_split(cdpath, ':');
	if (split == NULL)
		return (false);
	ret = get_path(split, dir, info);
	ptr_2d_free((void***)&split, -1);
	// if (srcdir_absolute_flag == false)
	// 	ret = false;
	return (ret);
}

void		go_to_path(t_minishell *info, char **dir,
				bool option_p_flag)
{
	bool	flag;
	bool	cd_path_flag;

	(void)option_p_flag;
	cd_path_flag = is_cd_path(info, dir);
	if (safe_chdir(*dir, NULL, info) == false)
		return ;
	info->oldpwd_path = re_strdup(&(info->oldpwd_path), info->current_dir_path);
	if (change_dir(*dir, info) == false)
		return ;
	when_double_slash_root(*dir, info);
	update_env_value(&(info->env), "PWD", info->current_dir_path, info);
	if (cd_path_flag)
		ft_putendl_fd(info->current_dir_path, STDOUT_FILENO);
	g_global.exit_status = 0;
}
