/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 13:03:51 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/10 13:04:12 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	not_set_home_path(t_minishell *info)
{
	if (write(STDERR, "minishell: cd: HOME not set\n", 28) < 28)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	g_global.exit_status = EXIT_FAILURE;
}

void	set_oldpwd(t_minishell *info, char *oldpwd)
{
	char	*pwd_path;

	g_global.info.current_dir_path = info->current_dir_path;
	pwd_path = ft_getenv("PWD", info->env, false);
	if (pwd_path == NULL || pwd_path[0] == '\0')
	{
		update_env_value(&(info->env), "OLDPWD", "", info);
	}
	else if (oldpwd)
	{
		update_env_value(&(info->env), "OLDPWD", oldpwd, info);
	}
}
