/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:26:24 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/04 03:01:19 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	key_ctrl_left_and_right(t_minishell *info)
{
	info->key.ctrl_lr_flag = true;
	return (NOTHING_KEY);
}

/*
** KEY_TAB and NOTHING_KEY have the same value
*/

static int	is_what_key(char *buf, char *command, t_minishell *info)
{
	if (buf[0] == 4 && command[0] == '\0')
		return (CTRL_D);
	else if (buf[0] == 12)
		return (CTRL_L);
	else if (buf[0] == 127)
		return (KEY_DELETE);
	else if (buf[0] == 10)
		return (KEY_NEWLINE);
	else if (buf[0] == 1)
		return (KEY_HOME);
	else if (buf[0] == 5)
		return (KEY_END);
	else if (buf[0] == 2)
		return (CTRL_B);
	else if (buf[0] == 6)
		return (CTRL_F);
	else if (buf[0] == 7)
		return (CTRL_G);
	else if (buf[0] == 25)
		return (CTRL_Y);
	else if (buf[0] == 11)
		return (CTRL_K);
	else if (buf[0] == 16)
		return (CTRL_P);
	else if (buf[0] == 14)
		return (CTRL_N);
	else if (info->minishell_op_no_edit == false && buf[0] == 9)
		return (KEY_TAB);
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 65)
		return (KEY_UP);
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 66)
		return (KEY_DOWN);
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 67)
		return (KEY_RIGHT);
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 68)
		return (KEY_LEFT);
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 49)
		return (key_ctrl_left_and_right(info));
	else if (info->key.ctrl_lr_flag == true)
	{
		if (buf[0] == 59 && buf[1] == 53 && buf[2] == 68)
			return (KEY_CTRL_LEFT);
		else if (buf[0] == 59 && buf[1] == 53 && buf[2] == 67)
			return (KEY_CTRL_RIGHT);
	}
	else if (ft_isprint(buf[0]))
		return (NORMAL_CHAR);
	return (NOTHING_KEY);
}

static void	init_selected_target(int key, t_string *command, t_minishell *info)
{
	if (key != CTRL_B && key != CTRL_F && key != CTRL_Y &&
		key != CTRL_K && key != CTRL_G)
	{
		if (info->key.target_end != -1 || info->key.target_start != -1)
		{
			move_direction(info->key.save_command_len - command->len,
				info->key.right, info);
			delete_displayed_command(info->key.save_command_len,
				info->key.left, info->key.clean_right);
			if (ft_putstr_fd(command->str, STDOUT) == false)
				all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
			move_direction(info->key.save_command_len - command->len,
				info->key.left, info);
		}
		info->key.target_end = -1;
		info->key.target_start = -1;
	}
}

void		check_key(char *buf, t_string *command, t_minishell *info)
{
	int		key;
	// printf("0[%s]\n", buf);
	// printf("1[%d]\n", buf[0]);
	// printf("2[%d]\n", buf[1]);
	// printf("3[%d]\n", buf[2]);
	// printf("4[%d]\n", buf[3]);
	// printf("^[[1;5D");
	// write(1, buf, strlen(buf));
	// ft_putchar_fd(*buf, STDOUT);
	// printf("\n[%s]\n", command->str);
	// 	printf("[%zd]\n", command->len);
	// 	printf("[%s]\n", command->str + command->len);
	// 	printf("[%zd]\n", info->key.save_command_len);
	void	(*const do_each_key[])(char *, t_string *, t_minishell *) = {
		trace_history_up, trace_history_down,
		move_cursor_left, move_cursor_right,
		ctrl_d_exit, clear_terminal, delete_displayed_char,
		print_user_pushed_char, pushed_newline,
		go_line_beginning, go_line_end, do_nothing,
		move_left_directly_word_toward, move_right_directly_word_toward,
		select_target_left, select_target_right,
		copy, paste, cut,
		move_up_one_line, move_down_one_line,
	};

	key = is_what_key(buf, command->str, info);
	init_selected_target(key, command, info);
	do_each_key[key](buf, command, info);
}
