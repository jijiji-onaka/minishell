/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_d_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 02:06:52 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/04 03:01:28 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ctrl_d_exit(char *buf, t_string *command, t_minishell *info)
{
	(void)buf;
	if (write(STDERR, "\033[0Kexit\n", 9) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	tcsetattr(STDIN, TCSANOW, &(g_global.terms[ORIGINAL]));
	update_command_history_file(info, info->command_history_begin);
	all_free_minishell_info(info);
	ptr_free((void **)&(command->str));
	exit(g_global.exit_status);
}
