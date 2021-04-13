/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_cdpath.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:29:24 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/10 15:21:29 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static bool	is_exist_dir(char **dir_1, char *dir_2, t_minishell *info)
{
	int			fd;

	connect_path(dir_1, dir_2, info);
	fd = open(*dir_1, O_RDONLY);
	if (fd == -1)
		return (false);
	close(fd);
	return (true);
}

static bool	connect_cdpath(char **dir_1, char *dir_2,
					DIR **dp, t_minishell *info)
{
	*dir_1 = re_strdup(dir_1, dir_2);
	if (*dir_1 == NULL)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	safe_closedir(dp, info);
	return (true);
}

static bool	get_path(char **split, char **dir, t_minishell *info)
{
	int				i;
	DIR				*dp;
	struct dirent	*dirp;

	i = -1;
	while (split[++i])
	{
		if (safe_opendir(&dp, split[i], info) == false)
			return (false);
		while (1)
		{
			if (safe_readdir(&dirp, dp, info) == false)
				break ;
			if (equal(ft_strcmp(dirp->d_name, *dir)))
			{
				if (dirp->d_name[0] == '.'
					|| is_exist_dir(&(split[i]), dirp->d_name, info) == false)
					continue ;
				return (connect_cdpath(dir, split[i], &dp, info));
			}
		}
		safe_closedir(&dp, info);
	}
	return (false);
}

bool	is_cdpath(t_minishell *info, char **dir)
{
	char		*cdpath;
	char		**split;
	bool		ret;

	cdpath = ft_getenv("CDPATH", info->env, false);
	if (cdpath == NULL || cdpath[0] == ':')
		return (false);
	split = ft_split(cdpath, ':');
	if (split == NULL)
		return (false);
	ret = get_path(split, dir, info);
	ptr_2d_free((void ***)&split, -1);
	return (ret);
}
