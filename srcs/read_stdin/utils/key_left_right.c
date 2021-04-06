/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_left_right.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:49:37 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/06 09:39:47 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// void	move_left(size_t len, )

void	move_cursor_left(char *buf, t_string *command, t_minishell *info)
{
	if (equal_pos(info->cursor.cur_pos, info->cursor.command_start_pos) == true)
		return;
	if (info->cursor.cur_pos[X] == LEFT_EDGE)
	{
		move_specified_position(info->cursor.cur_pos[Y] - 1,
			get_window_size_x(info), where_err(LINE, FILE), info);
	}
	else
		putstr_fd(info->key.left, STDIN, where_err(LINE, FILE), info);
	// if (command)
	// 	--command->len;
	handle_back_cursor_pos(info->cursor.cur_pos, get_window_size_x(info));
}

void	move_cursor_right(char *buf, t_string *command, t_minishell *info)
{
	t_ws	winsize;

	if (equal_pos(info->cursor.cur_pos, info->cursor.command_end_pos) == true)
		return ;
	winsize = get_window_size(info);
	if (winsize.ws_col == info->cursor.cur_pos[X])
	{
		putstr_fd(info->key.scroll_up, STDIN, where_err(LINE, FILE), info);
		move_specified_position(signed_min(info->cursor.cur_pos[Y] + 1,
			winsize.ws_row), 1, where_err(LINE, FILE), info);
	}
	else
		putstr_fd(info->key.right, STDIN, where_err(LINE, FILE), info);
	handle_forward_cursor_pos(info->cursor.cur_pos,
		info->cursor.command_start_pos, NULL, info);
}
