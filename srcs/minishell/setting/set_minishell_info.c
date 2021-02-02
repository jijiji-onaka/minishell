/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_minishell_info.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 01:51:29 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/27 19:20:56 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	set_minishell_info(t_minishell_info *info)
{
	info->current_dir_path = getcwd(NULL, 0);
	info->cmd_lst = NULL;
	info->cmd_lst_num = 0;
	info->env = NULL;
}
