/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_binfile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 14:23:17 by tjinichi          #+#    #+#             */
/*   Updated: 2021/05/16 15:07:22 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*check_executable_file_in_bin_dir(char *path, char **command,
				t_minishell *info)
{
	struct stat	stat_buf;
	char		*bin_path;

	if (lstat(path, &stat_buf) == 0)
	{
		if (path[ft_strlen(path) - 1] == '/' || (*command)[0] == '/')
			bin_path = ft_strjoin(path, command[0]);
		else
			bin_path = ft_str3join(path, "/", command[0]);
	}
	else
		return (NULL);
	if (bin_path == NULL)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	if (lstat(bin_path, &stat_buf) == 0)
		return (bin_path);
	ptr_free((void **)&bin_path);
	return (NULL);
}

bool	no_exe_file_in_bin_dir(char *file, t_minishell *info)
{
	DIR				*dir;
	struct dirent	*dp;
	bool			ret;

	ret = false;
	dir = opendir(info->current_dir_path);
	if (dir == NULL)
		all_free_exit(info, ERR_OPENDIR, __LINE__, __FILE__);
	while (1)
	{
		dp = readdir(dir);
		if (dp == NULL)
			break ;
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
