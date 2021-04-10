/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:26:24 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/09 12:17:25 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	init_selected_target(int key, t_string *command, t_minishell *info)
{
	int	original_pos;
	int	i;

	if (key != KEY_SHIFT_LEFT && key != KEY_SHIFT_RIGHT && key != CTRL_B &&
		key != KEY_SHIFT_UP && key != KEY_SHIFT_DOWN && key != TO_BE_CONTINUE)
	{
		original_pos = get_command_len_from_pos(info->cursor.command_end_pos,
							info->cursor.cur_pos, info);
		dup_pos(info->cursor.cur_pos, info->cursor.command_start_pos);
		dup_pos(info->cursor.command_end_pos, info->cursor.command_start_pos);
		move_specified_position(info->cursor.command_start_pos[Y],
			info->cursor.command_start_pos[X], where_err(LINE, FILE), info);
		command->len = 0;
		display_command(command, info);
		i = -1;
		while (++i < original_pos)
			move_cursor_left(NULL, NULL, info);
	}
}

// static int	warning_multibyte(char *buf, t_string *command, t_minishell *info)
// {
// 	putstr_fd("\nminishell: Only single-byte characters are supported.\n",
// 		STDERR, where_err(LINE, FILE), info);
// 	command->str[0] = '\0';
// 	buf[0] = '\n';
// 	return (KEY_NEWLINE);
// }

void		check_key(char *buf, t_string *command, t_minishell *info)
{
	int		key;
	// printf("0[%s]\n", buf);
	// printf("1[%d]\n", buf[0]);
	// printf("2[%d]\n", buf[1]);
	// printf("3[%d]\n", buf[2]);
	// printf("4[%d]\n", buf[3]);
	void	(*const do_each_key[])(char *, t_string *, t_minishell *) = {
		trace_history_up, trace_history_down,
		move_cursor_left, move_cursor_right,
		ctrl_d_exit, clear_terminal, delete_displayed_char,
		print_user_pushed_char, pushed_newline,
		go_command_beginning, go_command_end, do_nothing,
		move_word_directly_to_left, move_word_directly_to_right,
		select_target_left, select_target_right,
		copy_command, paste_selected_str, cut_command,
		move_up_one_line, move_down_one_line, do_nothing,
	};

	putstr_fd(info->key.cursor_visible, STDIN, where_err(LINE, FILE), info);
	key = get_key_id(buf, command, info);
	init_selected_target(key, command, info);
	do_each_key[key](buf, command, info);
	if (key != KEY_SHIFT_LEFT && key != KEY_SHIFT_RIGHT && key != CTRL_B
			&& key != TO_BE_CONTINUE)
		dup_pos(info->cursor.select_pos, info->cursor.cur_pos);
}

void		check_key_multiple_line(char multiple_line_char, char *buf, t_string *command, t_minishell *info)
{
	int		key;
	// printf("0[%s]\n", buf);
	// printf("1[%d]\n", buf[0]);
	// printf("2[%d]\n", buf[1]);
	// printf("3[%d]\n", buf[2]);
	// printf("4[%d]\n", buf[3]);
	void	(*const do_each_key[])(char *, t_string *, t_minishell *) = {
		trace_history_up, trace_history_down,
		move_cursor_left, move_cursor_right,
		ctrl_d_put_error, clear_terminal, delete_displayed_char,
		print_user_pushed_char, pushed_newline,
		go_command_beginning, go_command_end, do_nothing,
		move_word_directly_to_left, move_word_directly_to_right,
		select_target_left, select_target_right,
		copy_command, paste_selected_str, cut_command,
		move_up_one_line, move_down_one_line, do_nothing,
	};
	info->multiple_line_char = multiple_line_char;
	putstr_fd(info->key.cursor_visible, STDIN, where_err(LINE, FILE), info);
	key = get_key_id(buf, command, info);
	init_selected_target(key, command, info);
	do_each_key[key](buf, command, info);
	if (key != KEY_SHIFT_LEFT && key != KEY_SHIFT_RIGHT && key != CTRL_B
			&& key != TO_BE_CONTINUE)
		dup_pos(info->cursor.select_pos, info->cursor.cur_pos);
}
