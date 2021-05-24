/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_x_func_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 12:40:09 by tjinichi          #+#    #+#             */
/*   Updated: 2021/05/22 13:57:28 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bonus_includes/minishell_bonus.h"

static void	key_x_func_3(char *buf, t_string *command,
					t_minishell *info, int key)
{
	if (key == CTRL_P)
		move_up_one_line(buf, command, info);
	else if (key == CTRL_N)
		move_down_one_line(buf, command, info);
}

static void	key_x_func_2(char *buf, t_string *command,
					t_minishell *info, int key)
{
	if (key == KEY_HOME)
		go_command_beginning(buf, command, info);
	else if (key == KEY_END)
		go_command_end(buf, command, info);
	else if (key == NOTHING_KEY || key == TO_BE_CONTINUE)
		do_nothing(buf, command, info);
	else if (key == KEY_CTRL_LEFT)
		move_word_directly_to_left(buf, command, info);
	else if (key == KEY_CTRL_RIGHT)
		move_word_directly_to_right(buf, command, info);
	else if (key == KEY_SHIFT_LEFT)
		select_target_left(buf, command, info);
	else if (key == KEY_SHIFT_RIGHT)
		select_target_right(buf, command, info);
	else if (key == KEY_SHIFT_UP)
		copy_command(buf, command, info);
	else if (key == KEY_SHIFT_DOWN)
		cut_command(buf, command, info);
	else if (key == CTRL_B)
		paste_selected_str(buf, command, info);
	else
		key_x_func_3(buf, command, info, key);
}

void	key_x_func(char *buf, t_string *command, t_minishell *info, int key)
{
	if (key == KEY_UP)
		trace_history_up(buf, command, info);
	else if (key == KEY_DOWN)
		trace_history_down(buf, command, info);
	else if (key == KEY_LEFT)
		move_cursor_left(buf, command, info);
	else if (key == KEY_RIGHT)
		move_cursor_right(buf, command, info);
	else if (key == CTRL_D)
		ctrl_d_exit(buf, command, info);
	else if (key == CTRL_L)
		clear_terminal(buf, command, info);
	else if (key == KEY_DELETE)
		delete_displayed_char(buf, command, info);
	else if (key == NORMAL_CHAR)
		print_user_pushed_char(buf, command, info);
	else if (key == KEY_NEWLINE)
		pushed_newline(buf, command, info);
	else
		key_x_func_2(buf, command, info, key);
}

void	key_x_func_mul(char *buf, t_string *command, t_minishell *info, int key)
{
	if (key == KEY_UP)
		trace_history_up(buf, command, info);
	else if (key == KEY_DOWN)
		trace_history_down(buf, command, info);
	else if (key == KEY_LEFT)
		move_cursor_left(buf, command, info);
	else if (key == KEY_RIGHT)
		move_cursor_right(buf, command, info);
	else if (key == CTRL_D)
		ctrl_d_put_error(buf, command, info);
	else if (key == CTRL_L)
		clear_terminal(buf, command, info);
	else if (key == KEY_DELETE)
		delete_displayed_char(buf, command, info);
	else if (key == NORMAL_CHAR)
		print_user_pushed_char(buf, command, info);
	else if (key == KEY_NEWLINE)
		pushed_newline(buf, command, info);
	else
		key_x_func_2(buf, command, info, key);
}
