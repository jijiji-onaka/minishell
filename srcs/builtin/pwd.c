/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 20:58:34 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/17 00:38:38 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		exec_pwd(t_minishell *info, t_cmdlst *cmd)
{
	char	*working_dir;
	char	*option;

	option = cmd->arg[1];
	if (option != NULL)
		if (option[0] == '-' && option[1] != '\0')
			return (error_mandatory(ERR_PWD, 27, info));
	working_dir = info->current_dir_path;
	if (ft_putendl_fd(working_dir, STDOUT_FILENO) == false)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	g_signal.exit_status = 0;
}
