/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_chdir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 03:10:50 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/24 22:22:21 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool	safe_chdir(char *dir, char **split, t_minishell *info)
{
	char	*err;
	char	*tmp;

	if (dir[0] == '\0')
		tmp = ft_getenv("PWD", info->env, false);
	else
		tmp = dir;
	if (tmp == NULL || tmp[0] == '\0')
		tmp = info->current_dir_path;
	if (chdir(tmp) == -1)
	{
		if (!(err = ft_strjoin("cd: ", dir)))
		{
			if (split)
				ptr_2d_free((void***)&split, -1);
			all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
		}
		ft_perror(err);
		free(err);
		g_global.exit_status = EXIT_FAILURE;
		return (false);
	}
	return (true);
}
