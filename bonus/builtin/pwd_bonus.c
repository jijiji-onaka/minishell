/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 20:58:34 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/04 03:01:19 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

void		exec_pwd(t_minishell *info, t_cmdlst *cmd)
{
	char	*working_dir;
	char	*option;

	option = cmd->arg[1];
	if (option != NULL)
		if (option[0] == '-' && option[1] != '\0')
			return (error_mandatory(ERR_PWD, 27, info));
	working_dir = info->current_dir_path;
	if (ft_putendl_fd(working_dir, STDOUT) == false)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	g_global.exit_status = 0;
}
