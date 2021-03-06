/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_go_oldpwd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 17:51:27 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/10 13:01:42 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	go_oldpwd(t_minishell *info)
{
	char		*oldpwd_path;

	oldpwd_path = ft_getenv("OLDPWD", info->env, false);
	if (oldpwd_path == NULL)
	{
		if (write(STDERR, NO_OLDPWD, 30) < 0)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
		g_global.exit_status = EXIT_FAILURE;
		return ;
	}
	oldpwd_path = ft_strdup(oldpwd_path);
	if (oldpwd_path == NULL)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	if (safe_chdir(oldpwd_path, NULL, info) == false)
		return ;
	if (ft_putendl_fd(oldpwd_path, 1) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	set_oldpwd(info, info->current_dir_path);
	ptr_free((void **)&(info->current_dir_path));
	info->current_dir_path = oldpwd_path;
	g_global.exit_status = EXIT_SUCCESS;
}
