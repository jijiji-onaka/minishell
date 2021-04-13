/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:26:24 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/13 13:02:42 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	init_selected_target(int key, t_string *command, t_minishell *info)
{
	int	original_pos;
	int	i;

	if (key != KEY_SHIFT_LEFT && key != KEY_SHIFT_RIGHT && key != CTRL_B
		&& key != KEY_SHIFT_UP && key != KEY_SHIFT_DOWN
		&& key != TO_BE_CONTINUE)
	{
		if (equal_pos(info->cursor.cur_pos, info->cursor.select_pos) == false)
		{
			original_pos = get_command_len_from_pos(
					info->cursor.command_end_pos,
					info->cursor.cur_pos, info);
			dup_pos(info->cursor.cur_pos, info->cursor.command_start_pos);
			dup_pos(info->cursor.command_end_pos,
				info->cursor.command_start_pos);
			move_specified_position(info->cursor.command_start_pos[Y],
				info->cursor.command_start_pos[X], where_err(LINE, FILE), info);
			command->len = 0;
			display_command(command, info);
			i = -1;
			while (++i < original_pos)
				move_cursor_left(NULL, NULL, info);
		}
	}
}

void	check_key(char *buf, t_string *command, t_minishell *info)
{
	int	key;

	putstr_fd(info->key.cursor_visible, STDIN, where_err(LINE, FILE), info);
	key = get_key_id(buf, command, info);
	init_selected_target(key, command, info);
	key_x_func(buf, command, info, key);
	if (key != KEY_SHIFT_LEFT && key != KEY_SHIFT_RIGHT && key != CTRL_B
		&& key != TO_BE_CONTINUE)
		dup_pos(info->cursor.select_pos, info->cursor.cur_pos);
}

void	check_key_multiple_line(char multiple_line_char, char *buf,
					t_string *command, t_minishell *info)
{
	int	key;

	info->multiple_line_char = multiple_line_char;
	putstr_fd(info->key.cursor_visible, STDIN, where_err(LINE, FILE), info);
	key = get_key_id(buf, command, info);
	init_selected_target(key, command, info);
	key_x_func_mul(buf, command, info, key);
	if (key != KEY_SHIFT_LEFT && key != KEY_SHIFT_RIGHT && key != CTRL_B
		&& key != TO_BE_CONTINUE)
		dup_pos(info->cursor.select_pos, info->cursor.cur_pos);
}
