/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_del.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 01:48:20 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/09 13:53:32 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	edit_command(t_string *command, t_minishell *info)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*str;

	i = 0;
	j = 0;
	str = command->str;
	len = command->len - 1;
	while (str[i])
	{
		if (i != len)
			str[j++] = str[i];
		i++;
	}
	command->str[j] = '\0';
}

static void	erase_under_line(t_minishell *info, t_err err)
{
	putstr_fd(info->key.cursor_save, STDIN, err, info);
	move_specified_position(info->cursor.command_end_pos[Y],
		info->cursor.command_end_pos[X], where_err(LINE, FILE), info);
	putstr_fd(info->key.delete_line, STDIN, err, info);
	putstr_fd(info->key.cursor_restore, STDIN, err, info);
}

int	get_pos(t_string *command, t_cursor cursor)
{
	int		i;
	int		res;
	bool	flag;

	i = command->len - 1;
	flag = false;
	res = 0;
	while (i >= 0)
	{
		if (flag == true)
			res++;
		if (command->str[i] == '\n')
			flag = true;
		i--;
	}
	return (cursor.command_start_pos[X] + res);
}

void	delete_displayed_char(char *buf, t_string *command,
					t_minishell *info)
{
	int	winsize_x;

	(void)buf;
	winsize_x = get_window_size_x(info);
	// printf("[%c]\n", command->str[command->len - 1]);
	if (equal_pos(info->cursor.cur_pos, info->cursor.command_start_pos) == true)
		return ;
	if (info->cursor.command_end_pos[Y] != info->cursor.cur_pos[Y]
		|| (info->cursor.cur_pos[X] == LEFT_EDGE))
		erase_under_line(info, where_err(LINE, FILE));
	if (command->str[command->len - 1]== '\n')
		move_specified_position(info->cursor.cur_pos[Y] - 1,
			get_pos(command, info->cursor), where_err(LINE, FILE), info);
	else if (info->cursor.command_start_pos[Y] != info->cursor.cur_pos[Y]
		&& (info->cursor.cur_pos[X] == LEFT_EDGE))
		move_specified_position(info->cursor.cur_pos[Y] - 1,
			winsize_x, where_err(LINE, FILE), info);
	else
		putstr_fd(info->key.left, STDIN, where_err(LINE, FILE), info);
	putstr_fd(info->key.cursor_save, STDIN, where_err(LINE, FILE), info);
	putstr_fd(info->key.clean_right, STDIN, where_err(LINE, FILE), info);
	putstr_fd(command->str + command->len,
		STDIN, where_err(LINE, FILE), info);
	// putstr_fd(command->str + get_now_index(info, command),
	// 	STDIN, where_err(LINE, FILE), info);
	edit_command(command, info);
	putstr_fd(info->key.cursor_restore, STDIN, where_err(LINE, FILE), info);
	--command->len;
	handle_back_cursor_pos(info->cursor.cur_pos, winsize_x);
	handle_back_cursor_pos(info->cursor.command_end_pos, winsize_x);
}
