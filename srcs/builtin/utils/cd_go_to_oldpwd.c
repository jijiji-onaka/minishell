/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_go_to_oldpwd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 17:51:27 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/21 11:24:12 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void		go_to_oldpwd(t_minishell *info)
{
	char		*oldpwd_path;

	oldpwd_path = search_env("OLDPWD", 6, info->env, NULL);
	if (oldpwd_path == NULL)
	{
		if (write(STDERR_FILENO, NO_OLDPWD, 30) < 0)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
		g_signal.exit_status = EXIT_FAILURE;
		return ;
	}
	if (!(oldpwd_path = ft_strdup(oldpwd_path)))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	if (safe_chdir(oldpwd_path, NULL, info) == false)
		return ;
	if (ft_putendl_fd(oldpwd_path, 1) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	set_oldpwd(info, info->current_dir_path);
	ptr_free((void **)&(info->current_dir_path));
	info->current_dir_path = oldpwd_path;
	g_signal.exit_status = EXIT_SUCCESS;
}