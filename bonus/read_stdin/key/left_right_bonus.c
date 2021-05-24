/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_right_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:49:37 by tjinichi          #+#    #+#             */
/*   Updated: 2021/05/19 15:59:48 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bonus_includes/minishell_bonus.h"

void	move_cursor_left(char *buf, t_string *command, t_minishell *info)
{
	int	max_winsize_x;

	(void)buf;
	max_winsize_x = get_window_size(info).ws_col;
	if (equal_pos(info->cursor.cur_pos, info->cursor.command_start_pos) == true)
		return ;
	if (info->cursor.cur_pos[X] == LEFT_EDGE)
		move_specified_position(info->cursor.cur_pos[Y] - 1, signed_min(
				get_from_nl_to_nl(command, info->cursor, info->cursor.cur_pos),
				max_winsize_x), where_err(LINE, FILE), info);
	else
		putstr_fd(info->key.left, STDIN, where_err(LINE, FILE), info);
	handle_back_cursor_pos(command, info->cursor.cur_pos, info, max_winsize_x);
}

void	move_cursor_right(char *buf, t_string *command, t_minishell *info)
{
	struct winsize	winsize;
	int				len;

	(void)buf;
	if (equal_pos(info->cursor.cur_pos, info->cursor.command_end_pos) == true)
		return ;
	winsize = get_window_size(info);
	len = get_now_index(info, command);
	if (winsize.ws_col == info->cursor.cur_pos[X]
		|| (len != 0 && command->str[len] == '\n'))
	{
		putstr_fd(info->key.scroll_up, STDIN, where_err(LINE, FILE), info);
		move_specified_position(signed_min(info->cursor.cur_pos[Y] + 1,
				winsize.ws_row), LEFT_EDGE, where_err(LINE, FILE), info);
	}
	else
		putstr_fd(info->key.right, STDIN, where_err(LINE, FILE), info);
	if (len != 0 && command->str[len] == '\n')
		info->cursor.cur_pos[X] = winsize.ws_col;
	handle_forward_cursor_pos(info->cursor.cur_pos,
		info->cursor.command_start_pos, NULL, info);
}
