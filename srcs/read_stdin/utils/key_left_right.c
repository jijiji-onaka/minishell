/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_left_right.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:49:37 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/04 10:01:58 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	move_cursor_left(char *buf, t_string *command, t_minishell *info)
{
	if (equal_pos(info->cursor.cur_pos, info->cursor.command_start_pos) == true)
		return;
	if (info->cursor.command_start_pos[Y] != info->cursor.cur_pos[Y]
		&& (info->cursor.cur_pos[X] == LEFT_EDGE))
		move_specified_position(info->cursor.cur_pos[Y] - 1,
			info->window.ws.ws_col, where_err(LINE, FILE), info);
	else
		putstr_fd(info->key.left, STDIN, where_err(LINE, FILE), info);
	--command->len;
	handle_back_cursor_pos(info->cursor.cur_pos, info->window.ws.ws_col);
}

void	move_cursor_right(char *buf, t_string *command, t_minishell *info)
{
	if (equal_pos(info->cursor.cur_pos, info->cursor.command_end_pos) == true)
		return ;
	++command->len;
	++info->cursor.cur_pos[X];
	if (info->window.ws.ws_col + 1 == info->cursor.cur_pos[X])
	{
		putstr_fd(info->key.scroll_up, STDIN, where_err(LINE, FILE), info);
		handle_forward_cursor_pos(info->cursor.cur_pos,
			info->cursor.command_start_pos, info->window.ws.ws_row);
		move_specified_position(info->cursor.cur_pos[Y], 1,
			where_err(LINE, FILE), info);
	}
	else
		putstr_fd(info->key.right, STDIN, where_err(LINE, FILE), info);
}
