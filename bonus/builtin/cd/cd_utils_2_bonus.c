/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils_2_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 13:03:51 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/13 14:03:24 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bonus_includes/minishell_bonus.h"

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
