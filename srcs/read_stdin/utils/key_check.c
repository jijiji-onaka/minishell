/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:26:24 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/29 17:37:49 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	is_what_key(char *buf, char *command)
{
	if (buf[0] == 4 && command[0] == '\0')
		return (CTRL_D);
	else if (buf[0] == 12)
		return (CTRL_L);
	else if (buf[0] == 127)
		return (KEY_DELETE);
	else if (buf[0] == 10)
		return (KEY_NEWLINE);
	// if (!(buf[0] == 27 && buf[1] == 91))
	// 	return (NORMAL_CHAR);
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 65)
		return (KEY_UP);
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 66)
		return (KEY_DOWN);
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 67)
		return (KEY_RIGHT);
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 68)
		return (KEY_LEFT);
	return (NORMAL_CHAR);
}

void		check_key(char *buf, t_string *command, t_minishell *info)
{
	int		key;
	void	(*const do_each_key[])(char *, t_string *, t_minishell *) = {
		trace_history_up, trace_history_down,
		move_cursor_left, move_cursor_right,
		ctrl_d_exit, clear_terminal, delete_displayed_char,
		print_user_pushed_char, pushed_newline,
	};

	key = is_what_key(buf, command->str);
	do_each_key[key](buf, command, info);
}
