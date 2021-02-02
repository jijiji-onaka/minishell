/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mandatory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 02:11:42 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 16:59:51 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	error_mandatory(char *err_message, int num, t_minishell_info *info)
{
	red_error();
	if (write(STDERR_FILENO, err_message, num) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	return ;
}
