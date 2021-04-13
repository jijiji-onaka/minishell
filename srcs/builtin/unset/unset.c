/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 18:44:56 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/10 14:17:01 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	exec_unset(t_minishell *info, t_cmdlst *cmd)
{
	int		i;
	char	**args;

	args = cmd->arg;
	g_global.exit_status = 0;
	if (args[1] == NULL)
		return ;
	if (args[1][0] == '-')
		return (error_mandatory(ERR_UNSET, 29, info));
	i = 0;
	while (args[++i])
	{
		if (is_valid_env_name(&(args[i]), args[i], info))
		{
			if (ft_strcmp(args[i], "PWD") == MATCH)
				g_global.info.unset_pwd_flag = true;
			else if (ft_strcmp(args[i], "OLDPWD") == MATCH)
				g_global.info.unset_oldpwd_flag = true;
			remove_env_lst_if(&(info->env), args[i]);
		}
	}
}
