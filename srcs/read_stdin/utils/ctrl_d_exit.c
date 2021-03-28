/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_d_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 02:06:52 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/28 06:38:37 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ctrl_d_exit(char **ptr, t_minishell *info)
{
	if (write(STDERR_FILENO, "\033[0Kexit\n", 9) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	tcsetattr(STDIN_FILENO, TCSANOW, &(g_global.terms[ORIGINAL]));
	all_free_minishell_info(info);
	ptr_free((void **)ptr);
	exit(g_global.exit_status);
}
