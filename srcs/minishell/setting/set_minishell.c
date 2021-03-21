/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_minishell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 16:01:47 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/21 15:04:23 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	set_minishell(t_minishell *info)
{
	info->cmd_lst = NULL;
	info->cwd_err_f = 0;
	info->cmd_lst_num = 0;
	info->exit_too_arg = 0;
	info->env = NULL;
	info->ptr_for_free = NULL;
	info->ptr_for_free_2 = NULL;
	info->ptr_2d_for_free = NULL;
}
