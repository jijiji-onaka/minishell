/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_go_to_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 17:43:47 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/21 20:20:03 by tjinichi         ###   ########.fr       */
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
			update_current_dir(info, split[i]);
		free(new);
	}
	ptr_2d_free((void***)&(split), -1);
	info->ptr_2d_for_free = NULL;
	return (true);
}

static bool	ch_root_dir_when_arg_is_absolute(t_minishell *info, bool flag)
{
	if (flag)
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

	if (!(oldpwd = ft_strdup(search_env("PWD", 3, info->env, NULL))))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	if (ch_root_dir_when_arg_is_absolute(info, dir[0] == '/') == false)
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

void		go_to_path(t_minishell *info, char **dir,
				bool option_p_flag)
{
	bool	flag;

	(void)option_p_flag;
	if (safe_chdir(*dir, NULL, info) == false)
		return ;
	if (change_dir(*dir, info) == false)
		return ;
	when_double_slash_root(*dir, info);
	update_env_lst(&(info->env), "PWD", info->current_dir_path, info);
	info->cwd_err_f = 0;
	g_signal.exit_status = 0;
}
