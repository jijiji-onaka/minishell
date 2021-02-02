/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_symbolic_link.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 00:55:25 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 20:37:53 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool	is_symbolic_dir(t_minishell_info *info, char *dir_name)
{
	t_stat	stat_buf;

	if (lstat(dir_name, &stat_buf) == -1)
	{
		if (errno == EFAULT || errno == ELOOP || errno == ENOMEM)
			all_free_exit(info, ERR_LSTAT, __LINE__, __FILE__);
		return (false);
	}
	if (S_ISLNK(stat_buf.st_mode) == 0 || S_ISDIR(stat_buf.st_mode))
		return (false);
	return (true);
}
