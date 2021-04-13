/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:22:24 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/10 14:53:23 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	safe_opendir(DIR **dp, char *dir, t_minishell *info)
{
	*dp = opendir(dir);
	if (*dp == NULL && errno == ENOENT)
		return (false);
	if (*dp == NULL)
		all_free_exit(info, ERR_OPENDIR, __LINE__, __FILE__);
	return (true);
}

bool	safe_readdir(struct dirent **dirp, DIR *dp, t_minishell *info)
{
	*dirp = readdir(dp);
	if (*dirp != NULL)
		return (true);
	(void)info;
	return (false);
}

void	safe_closedir(DIR **dp, t_minishell *info)
{
	if (closedir(*dp) == -1)
		all_free_exit(info, ERR_CLOSEDIR, __LINE__, __FILE__);
}
