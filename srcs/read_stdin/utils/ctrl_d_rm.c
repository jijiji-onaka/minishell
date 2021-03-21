/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_d_rm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 18:48:08 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/19 18:50:55 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ctrl_d_rm(char **ptr, t_minishell *info)
{
	if (write(STDERR_FILENO, "\033[0K", 4) < 0)
	{
		ptr_free((void **)ptr);
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	}
}
