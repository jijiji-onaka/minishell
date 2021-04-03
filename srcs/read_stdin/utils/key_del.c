/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_del.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 01:48:20 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/04 03:02:40 by tjinichi         ###   ########.fr       */
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
	if (command->len == 0)
		len = 0;
	else
		len = command->len - 1;
	while (str[i])
	{
		if (i != len)
			str[j++] = str[i];
		i++;
	}
	command->str[j] = '\0';
	info->key.save_command_len = j;
}

static void	erase_under_line(t_minishell *info, t_err err)
{
	putstr_fd(info->key.save, STDIN, err, info);
	move_specified_position(
		info->cursor.command_end_pos[Y],
		info->cursor.command_end_pos[X],
		numlen(info->cursor.cur_pos[Y], info->window, Y),
		numlen(info->cursor.command_end_pos[X], info->window, X));
	putstr_fd(info->key.delete_line, STDIN, err, info);
	putstr_fd(info->key.restore, STDIN, err, info);
}

static void	move_right_end_of_line_above(t_minishell *info, t_err err)
{
	putstr_fd(info->key.save, STDIN, err, info);
	move_specified_position(
		info->cursor.command_end_pos[Y],
		info->cursor.command_end_pos[X],
		numlen(info->cursor.cur_pos[Y], info->window, Y),
		numlen(info->cursor.command_end_pos[X], info->window, X));
	putstr_fd(info->key.delete_line, STDIN, err, info);
	putstr_fd(info->key.restore, STDIN, err, info);
}

static void	treat_cursor_pos(t_cursor *cursor, int window_max_x)
{
	if (cursor->cur_pos[X] == LEFT_EDGE)
	{
		cursor->cur_pos[X] = window_max_x;
		if (cursor->cur_pos[Y] != UPPER_EDGE)
			--cursor->cur_pos[Y];
	}
	else
		--cursor->cur_pos[X];
	if (cursor->command_end_pos[X] == LEFT_EDGE)
	{
		cursor->command_end_pos[X] = window_max_x;
		if (cursor->command_end_pos[Y] != UPPER_EDGE)
			--cursor->command_end_pos[Y];
	}
	else
		--cursor->command_end_pos[X];
}

void		delete_displayed_char(char *buf, t_string *command,
					t_minishell *info)
{
	if (command->len == 0)
		return ;
	if (info->cursor.command_end_pos[Y] != info->cursor.cur_pos[Y]
		|| info->cursor.cur_pos[X] == LEFT_EDGE)
		erase_under_line(info, where_err(LINE, FILE));
	if (info->cursor.command_start_pos[Y] != info->cursor.cur_pos[Y]
		&& (info->cursor.cur_pos[X] == LEFT_EDGE))
		move_specified_position(
			info->cursor.cur_pos[Y] - 1,
			info->window.ws.ws_col ,
			numlen(info->cursor.cur_pos[Y] - 1, info->window, Y),
			numlen(info->window.ws.ws_col, info->window, X));
	else
		putstr_fd(info->key.left, STDIN, where_err(LINE, FILE), info);
	putstr_fd(info->key.save, STDIN, where_err(LINE, FILE), info);
	putstr_fd(info->key.clean_right, STDIN, where_err(LINE, FILE), info);
	putstr_fd(command->str + command->len, STDIN, where_err(LINE, FILE), info);
	edit_command(command, info);
	putstr_fd(info->key.restore, STDIN, where_err(LINE, FILE), info);
	--command->len;
	treat_cursor_pos(&(info->cursor), info->window.ws.ws_col);
}

bool		delete_displayed_command(size_t len, char *left, char *clean_right)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (ft_putstr_fd(left, STDIN) == false)
			return (false);
		i++;
	}
	if (ft_putstr_fd(clean_right, STDIN) == false)
		return (false);
	return (true);
}
