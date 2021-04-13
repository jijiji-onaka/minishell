/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_ctrl_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 02:06:52 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/08 08:20:50 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bonus_includes/minishell_bonus.h"

void	ctrl_d_exit(char *buf, t_string *command, t_minishell *info)
{
	(void)buf;
	if (write(STDERR, "\033[0Kexit\n", 9) < 9)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	tcsetattr(STDIN, TCSANOW, &(info->terminal[ORIGINAL]));
	ptr_free((void **)&(command->str));
	info->history.list->command = command->str;
	update_command_history_file(info, info->history.begin);
	all_free_minishell_info(info);
	exit(g_global.exit_status);
}

void	ctrl_d_put_error(char *buf, t_string *command, t_minishell *info)
{
	if (info->multiple_line_char != '|')
	{
		if (write(STDERR, SYNTAX_1, 54) < 54)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
		if (write(STDERR, &(info->multiple_line_char), 1) < 1)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
		if (write(STDERR, "`\n", 2) < 2)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	}
	if (write(STDERR, SYNTAX_2, 48) < 48)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	g_global.reading = false;
}
