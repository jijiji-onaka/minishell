/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_exefile_bin_dir.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 14:23:17 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/24 22:22:32 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char		*check_executable_file_in_bin_dir(char *path, char **command,
				t_minishell *info)
{
	t_stat	stat_buf;
	char	*bin_path;

	if (!(bin_path = ft_str3join(path, "/", command[0])))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	if (lstat(bin_path, &stat_buf) == 0)
	{
		return (bin_path);
	}
	ptr_free((void **)&bin_path);
	return (false);
}

bool		no_exe_file_in_bin_dir(char *file, t_minishell *info)
{
	DIR				*dir;
	struct dirent	*dp;
	bool			ret;

	ret = false;
	if ((dir = opendir(info->current_dir_path)) == NULL)
		all_free_exit(info, ERR_OPENDIR, __LINE__, __FILE__);
	while ((dp = readdir(dir)) != NULL)
	{
		if (ft_strcmp(file, dp->d_name) == 0)
		{
			ret = true;
			break ;
		}
	}
	if (errno != 0)
		NULL;
	if (closedir(dir) == -1)
		NULL;
	return (ret);
}

int			check_bash_standard_commands(t_minishell *info, char **command
				, bool *path_flag)
{
	char		*env_path;
	char		**bin_paths;
	int			i;

	if ((*command) == NULL || (*command)[0] == '\0')
		return (true);
	if (ft_strchr((*command), '/') || (ft_strcmp((*command), "..") == 0))
		return (true);
	if (!(env_path = ft_getenv("PATH", info->env, false)))
		return ((*path_flag = true));
	if (env_path[0] == '\0')
		return ((*path_flag = true));
	if (!(bin_paths = ft_split(env_path, ':')))
		return (-1);
	i = -1;
	while (bin_paths[++i])
		if (check_executable_file_in_bin_dir(bin_paths[i], command, info))
			return (!(ptr_2d_free((void ***)&bin_paths, i)));
	if ((env_path[ft_strlen(env_path) - 1] == ':' || env_path
[ft_strlen(env_path) - 1] == '/') && no_exe_file_in_bin_dir(*command, info))
		*command = re_strjoin(command, "./", *command);
	return (!(ptr_2d_free((void ***)&bin_paths, i)));
}
