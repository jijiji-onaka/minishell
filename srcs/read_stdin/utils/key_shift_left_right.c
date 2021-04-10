/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_shift_left_right.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 21:54:06 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/04 10:30:35 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	swap(int *x, int *y)
{
	int	tmp;

	tmp = *x;
	*x = *y;
	*y = tmp;
}

static void	put_selected_target(t_minishell *info, t_string *command)
{
	int		index;
	int		end;

	index = get_command_len_from_pos(info->cursor.select_pos,
				info->cursor.command_start_pos, info);
	end = get_command_len_from_pos(info->cursor.cur_pos,
				info->cursor.command_start_pos, info);
	if (index > end)
	{
		swap(&index, &end);
		move_specified_position(info->cursor.cur_pos[Y],
			info->cursor.cur_pos[X], where_err(LINE, FILE), info);
	}
	else
		move_specified_position(info->cursor.select_pos[Y],
			info->cursor.select_pos[X], where_err(LINE, FILE), info);
	putstr_fd(info->key.color_change, STDIN, where_err(LINE, FILE), info);
	while (index < end)
		putchar_fd(command->str[index++], STDIN, where_err(LINE, FILE), info);
	putstr_fd(info->key.color_reset, STDIN, where_err(LINE, FILE), info);
}

void		select_target_left(char *buf, t_string *command, t_minishell *info)
{
	(void)buf;
	info->key.shift_ctrl_lr_flag = false;
	if (equal_pos(info->cursor.select_pos, info->cursor.command_start_pos)
		== true)
		return ;
	move_specified_position(info->cursor.command_start_pos[Y],
		info->cursor.command_start_pos[X], where_err(LINE, FILE), info);
	putstr_fd(command->str, STDIN, where_err(LINE, FILE), info);
	putstr_fd(info->key.cursor_save, STDIN, where_err(LINE, FILE), info);
	putstr_fd(info->key.cursor_invisible, STDIN, where_err(LINE, FILE), info);
	handle_back_cursor_pos(info->cursor.select_pos, get_window_size_x(info));
	put_selected_target(info, command);
	putstr_fd(info->key.cursor_restore, STDIN, where_err(LINE, FILE), info);
}

void		select_target_right(char *buf, t_string *command, t_minishell *info)
{
	(void)buf;
	info->key.shift_ctrl_lr_flag = false;
	if (equal_pos(info->cursor.select_pos, info->cursor.command_end_pos)
		== true)
		return ;
	putstr_fd(info->key.cursor_save, STDIN, where_err(LINE, FILE), info);
	move_specified_position(info->cursor.command_start_pos[Y],
		info->cursor.command_start_pos[X], where_err(LINE, FILE), info);
	putstr_fd(command->str, STDIN, where_err(LINE, FILE), info);
	putstr_fd(info->key.cursor_restore, STDIN, where_err(LINE, FILE), info);
	putstr_fd(info->key.cursor_invisible, STDIN, where_err(LINE, FILE), info);
	handle_forward_cursor_pos(info->cursor.select_pos,
			NULL, NULL, info);
	put_selected_target(info, command);
	putstr_fd(info->key.cursor_restore, STDIN, where_err(LINE, FILE), info);
}
