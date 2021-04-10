/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_go_to_cwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 17:31:39 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/08 07:57:27 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static bool	when_cwd_is_not_symbolic(t_minishell *info, char *each_dir,
							char *arg_dir)
{
	(void)each_dir;
	(void)arg_dir;
	update_env_value(&(info->env), "PWD", info->current_dir_path, info);
	g_global.exit_status = 0;
	return (true);
}

static bool	when_cwd_is_symbolic(t_minishell *info, char *dir)
{
	char	*new;

	if (!(new = getcwd(NULL, 0)))
		return (not_found_cwd(info, dir, NULL));
	ptr_free((void **)&(info->current_dir_path));
	info->current_dir_path = new;
	g_global.exit_status = 0;
	return (true);
}

bool		go_to_cwd(t_minishell *info, char *dir, char *arg_dir)
{
	if (is_symbolic_dir(info, info->current_dir_path))
		return (when_cwd_is_symbolic(info, arg_dir));
	else
		return (when_cwd_is_not_symbolic(info, dir, arg_dir));
}
