/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 20:58:34 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 17:04:00 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** commandがpwdだった時の処理関数
*/

void		exec_pwd(t_minishell_info *info)
{
	if (ft_putendl_fd(info->current_dir_path, 1) == false)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
}
