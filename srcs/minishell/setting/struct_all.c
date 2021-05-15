/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 16:01:47 by tjinichi          #+#    #+#             */
/*   Updated: 2021/05/13 00:00:34 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	set_minishell(t_minishell *info)
{
	t_history	history;

	info->cmd_lst = NULL;
	info->cmd_lst_num = 0;
	info->exit_too_arg = 0;
	info->unset_pwd_flag = false;
	info->unset_oldpwd_flag = false;
	info->minishell_op_no_edit = false;
	info->env = NULL;
	history.file_path = "./.minishell_history";
	history.list = NULL;
	info->history = history;
	info->ptr_for_free = NULL;
	info->ptr_for_free_2 = NULL;
	info->ptr_2d_for_free = NULL;
	info->key.target = NULL;
	set_shell_level();
	set_env(info);
	set_command_history(info);
	info->current_dir_path = getcwd(NULL, 0);
	if (info->current_dir_path == NULL)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	info->oldpwd_path = ft_strdup(ft_getenv("OLDPWD", info->env, false));
	if (info->oldpwd_path == NULL)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
}
