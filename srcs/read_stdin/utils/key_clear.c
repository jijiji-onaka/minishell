/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:51:59 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/04 03:37:58 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	treat_cursor_pos(int pos[2], int start_pos[2], int window_max_y)
{
	if (window_max_y != pos[Y])
		pos[Y]++;
	if (start_pos[Y] != UPPER_EDGE)
		start_pos[Y]--;
	pos[X] = LEFT_EDGE;
}

static void	re_print_user_pushed_char(t_string *command, t_minishell *info)
{
	size_t i;

	i = -1;
	while (command->str[++i])
	{
		if (write(STDOUT, command->str + i, 1) < 1)
			all_free_exit(info, ERR_WRITE, LINE, FILE);
		++info->cursor.cur_pos[X];
		++info->cursor.command_end_pos[X];
		if (info->window.ws.ws_col + 1 == info->cursor.command_end_pos[X])
			treat_cursor_pos(info->cursor.command_end_pos,
							 info->cursor.command_start_pos, info->window.ws.ws_row);
		if (info->window.ws.ws_col + 1 == info->cursor.cur_pos[X])
		{
			putstr_fd(info->key.scroll_up, STDIN, where_err(LINE, FILE), info);
			treat_cursor_pos(info->cursor.cur_pos,
							 info->cursor.command_start_pos, info->window.ws.ws_row);
			move_specified_position(info->cursor.cur_pos[Y], 1,
									numlen(info->cursor.cur_pos[Y], info->window, Y), 1);
		}
	}
	command->len = i;
	info->key.save_command_len = i;
}

void		clear_terminal(char *buf, t_string *command, t_minishell *info)
{

	(void)buf;
	putstr_fd(info->key.clean, STDOUT, where_err(LINE, FILE), info);
	put_prompt(info);
	dup_pos(info->cursor.cur_pos, info->cursor.command_start_pos);
	dup_pos(info->cursor.command_end_pos, info->cursor.command_start_pos);
	re_print_user_pushed_char(command, info);
}
