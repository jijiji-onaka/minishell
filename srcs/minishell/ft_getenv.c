/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 19:18:45 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/24 20:53:40 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_getenv(char *str, t_envlst *env_lst, bool get_shell_val)
{
	while (env_lst)
	{
		if (ft_strcmp(env_lst->env.key.str, str) == MATCH)
			return (env_lst->env.value.str);
		env_lst = env_lst->next;
	}
	if (get_shell_val && g_global.info.unset_pwd_flag == false
		&& ft_strcmp("PWD", str) == MATCH)
		return (g_global.info.current_dir_path);
	if (get_shell_val && g_global.info.unset_oldpwd_flag == false
		&& ft_strcmp("OLDPWD", str) == MATCH)
		return (g_global.info.oldpwd_path);
	return (NULL);
}
