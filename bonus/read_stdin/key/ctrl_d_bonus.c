/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_ctrl_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 02:06:52 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/08 08:20:50 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bonus_includes/minishell_bonus.h"

static void	delete_cursor_pos_char(t_string *command, t_minishell *info)
{
	int	index;
	int	i;
	int	j;

	index = command->len - get_command_len_from_pos(
			info->cursor.command_end_pos, info->cursor.cur_pos, info);
	i = -1;
	j = -1;
	while (command->str[++i])
	{
		if (i != index)
			command->str[++j] = command->str[i];
	}
	command->str[++j] = '\0';
	command->len -= 1;
	putstr_fd(info->key.cursor_save, STDIN, where_err(LINE, FILE), info);
	putstr_fd(info->key.clean_right, STDIN, where_err(LINE, FILE), info);
	putstr_fd(command->str + index, STDIN, where_err(LINE, FILE), info);
	putstr_fd(info->key.cursor_restore, STDIN, where_err(LINE, FILE), info);
	handle_forward_cursor_pos(info->cursor.cur_pos,
		info->cursor.command_start_pos, NULL, info);
}

void	ctrl_d_exit(char *buf, t_string *command, t_minishell *info)
{
	(void)buf;
	if (command->str[0] != '\0')
		return (delete_cursor_pos_char(command, info));
	if (write(STDERR, "\033[0Kexit\n", 9) < 9)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (info->minishell_op_c == false)
		tcsetattr(STDIN, TCSANOW, &(info->terminal[ORIGINAL]));
	ptr_free((void **)&(command->str));
	info->history.list->command = command->str;
	update_command_history_file(info, info->history.begin);
	all_free_minishell_info(info);
	exit(g_global.exit_status);
}

void	ctrl_d_put_error(char *buf, t_string *command, t_minishell *info)
{
	(void)buf;
	(void)command;
	if (info->cursor.cur_pos[X] != info->cursor.command_end_pos[X])
		return (delete_cursor_pos_char(command, info));
	if (info->multiple_line_char != '|')
	{
		if (write(STDERR, SYNTAX_1, 54) < 54)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
		if (write(STDERR, &(info->multiple_line_char), 1) < 1)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
		if (write(STDERR, "`\n", 2) < 2)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	}
	if (write(STDERR, SYNTAX_2, 48) < 48)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	g_global.exit_status = 258;
	g_global.reading = false;
}
