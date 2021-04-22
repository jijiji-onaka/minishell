/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 01:48:20 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/22 18:19:50 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	edit_command(t_string *command, t_minishell *info)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = command->len - 1;
	len = get_now_index(info, command);
	while (command->str[i])
	{
		if (i != len)
			command->str[j++] = command->str[i];
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

static void	output(t_minishell *info, t_string *command)
{
	putstr_fd(info->key.cursor_save, STDIN, where_err(LINE, FILE), info);
	putstr_fd(info->key.clean_right, STDIN, where_err(LINE, FILE), info);
	putstr_fd(command->str + get_now_index(info, command), STDIN,
		where_err(LINE, FILE), info);
	putstr_fd(info->key.cursor_restore, STDIN, where_err(LINE, FILE), info);
}

void	delete_displayed_char(char *buf, t_string *command,
					t_minishell *info)
{
	int	max_winsize_x;

	(void)buf;
	max_winsize_x = get_window_size(info).ws_col;
	if (equal_pos(info->cursor.cur_pos, info->cursor.command_start_pos) == true)
		return ;
	if (info->cursor.command_end_pos[Y] != info->cursor.cur_pos[Y]
		|| (info->cursor.cur_pos[X] == LEFT_EDGE))
		erase_under_line(info, where_err(LINE, FILE));
	if (info->cursor.command_start_pos[Y] != info->cursor.cur_pos[Y]
		&& (info->cursor.cur_pos[X] == LEFT_EDGE))
		move_specified_position(info->cursor.cur_pos[Y] - 1,
			signed_min(get_from_nl_to_nl(command, info->cursor,
					info->cursor.cur_pos), max_winsize_x),
			where_err(LINE, FILE), info);
	else
		putstr_fd(info->key.left, STDIN, where_err(LINE, FILE), info);
	handle_back_cursor_pos(command, info->cursor.command_end_pos,
		info, max_winsize_x);
	handle_back_cursor_pos(command, info->cursor.cur_pos, info, max_winsize_x);
	edit_command(command, info);
	--command->len;
	output(info, command);
}
