/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_builtin_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 16:25:22 by tjinichi          #+#    #+#             */
/*   Updated: 2021/05/22 13:44:08 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bonus_includes/minishell_bonus.h"

bool	search_files(char *dir_name, char *file_name, t_minishell *info)
{
	DIR				*dp;
	struct dirent	*dirp;

	if (safe_opendir(&dp, dir_name, info) == false)
		return (false);
	while (1)
	{
		if (safe_readdir(&dirp, dp, info) == false)
			break ;
		if (dirp->d_name[0] == '.')
			continue ;
		if (equal(ft_strcmp(dirp->d_name, file_name)))
		{
			safe_closedir(&dp, info);
			return (true);
		}
	}
	safe_closedir(&dp, info);
	return (false);
}

bool	is_cwd_in_path(char *path, t_minishell *info)
{
	char	**split;
	int		i;
	bool	ret;

	split = ft_split(path, ':');
	if (split == NULL)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	i = -1;
	ret = false;
	while (split[++i])
	{
		if (split[i][0] == '.')
			ret = true;
	}
	ptr_2d_free((void ***)&split, i);
	return (ret);
}
