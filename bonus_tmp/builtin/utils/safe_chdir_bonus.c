/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_chdir_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 03:10:50 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/21 20:26:58 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell_bonus.h"

bool	safe_chdir(char *dir, char **split, t_minishell *info)
{
	char	*err;
	char	*tmp;

	if (dir[0] == '\0')
		tmp = search_env("PWD", 3, info->env, NULL);
	else
		tmp = dir;
	if (tmp == NULL || tmp[0] == '\0')
		tmp = info->current_dir_path;
	if (chdir(tmp) == -1)
	{
		if (!(err = ft_strjoin("cd: ", dir)))
		{
			ptr_2d_free((void***)&split, -1);
			all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
		}
		ft_perror(err);
		free(err);
		g_signal.exit_status = EXIT_FAILURE;
		return (false);
	}
	return (true);
}
