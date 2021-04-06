/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 23:22:47 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/06 15:15:09 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	move_direction(size_t len, char *direction, t_minishell *info)
{
	size_t	i;

	i = 0;
	while (i < len)
	{

		if (ft_putstr_fd(direction, STDIN) == false)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
		i++;
	}
}

int		numlen(int num, t_ws winsize, int x_y, t_minishell *info)
{
	if (num >= 0 && num < 10)
		return (1);
	else if (num >= 10 && num < 100)
		return (2);
	else if (num >= 100 && num < 1000)
		return (3);
	if (x_y == X)
		return (winsize.ws_col);
	else if (x_y == Y || true)
		return (winsize.ws_row);
}

static bool	move_specified_position_main(int pos_y, int pos_x, int y_len, int x_len)
{
	char	str[y_len + x_len + 5];
	uint	i;
	uint	total;

	str[0] = '\x1b';
	str[1] = '[';
	i = 1 + y_len;
	while (pos_y != 0)
	{
		str[1 + y_len--] = pos_y % 10 + '0';
		pos_y /= 10;
	}
	str[i++ + 1] = ';';
	total = i + x_len + 1;
	while (pos_x != 0)
	{
		str[i + x_len--] = pos_x % 10 + '0';
		pos_x /= 10;
	}
	str[total++] = 'H';
	str[total] = '\0';
	if (write(STDIN, str, total) == false)
		return (false);
	return (true);
}

void	move_specified_position(int pos_y, int pos_x, t_err err,
					t_minishell *info)
{
	int		y_len;
	int		x_len;
	t_ws	winsize;

	winsize = get_window_size(info);
	y_len = numlen(pos_y, winsize, Y, info);
	x_len = numlen(pos_x, winsize, X, info);
	if (move_specified_position_main(pos_y, pos_x, y_len, x_len) == false)
		all_free_exit(info, ERR_WRITE, err.line, err.file);
}

void	dup_pos(int dst[2], int src[2])
{
	dst[X] = src[X];
	dst[Y] = src[Y];
}

bool	equal_pos(int cmp_1[2], int cmp_2[2])
{
	if (cmp_1 == NULL || cmp_2 == NULL)
		return (false);
	if (cmp_1[X] - cmp_2[X] != 0)
		return (false);
	if (cmp_1[Y] - cmp_2[Y] != 0)
		return (false);
	return (true);
}

// void	handle_forward_cursor_pos(int pos[2],
// 			int start_pos[2], int end_pos[2], t_minishell *info)
// {
// 	t_ws	winsize;

// 	winsize = get_window_size(info);
// 	if (is_right_edge(winsize, end_pos))
// 	{
// 		if (is_win_bottom_edge(winsize, end_pos))
// 		{
// 			pos[Y] = int_max(0, pos[Y] - 1);
// 			start_pos[Y] = int_max(0, start_pos[Y] - 1);
// 		}
// 		end_pos[Y] = int_min(winsize.ws_row, end_pos[Y] + 1);
// 		end_pos[X] = LEFT_EDGE;
// 	}
// 	else if (end_pos)
// 		end_pos[X]++;
// 	if (is_right_edge(winsize, pos))
// 	{
// 		pos[Y] = int_min(winsize.ws_row, pos[Y] + 1);
// 		pos[X] = LEFT_EDGE;
// 	}
// 	else if (pos)
// 		pos[X]++;
// }

// void	handle_back_cursor_pos(int pos[2], int window_max_x)
// {
// 	if (pos[X] == LEFT_EDGE)
// 	{
// 		pos[X] = window_max_x;
// 		if (pos[Y] != UPPER_EDGE)
// 			--pos[Y];
// 	}
// 	else
// 		--pos[X];
// }

// void	handle_back_cursor_pos(t_cursor *cursor, int window_max_x)
// {
// 	if (cursor->cur_pos[X] == LEFT_EDGE)
// 	{
// 		cursor->cur_pos[X] = window_max_x;
// 		if (cursor->cur_pos[Y] != UPPER_EDGE)
// 			--cursor->cur_pos[Y];
// 	}
// 	else
// 		--cursor->cur_pos[X];
// 	if (cursor->command_end_pos[X] == LEFT_EDGE)
// 	{
// 		cursor->command_end_pos[X] = window_max_x;
// 		if (cursor->command_end_pos[Y] != UPPER_EDGE)
// 			--cursor->command_end_pos[Y];
// 	}
// 	else
// 		--cursor->command_end_pos[X];
// }

void	scroll_window(t_minishell *info, t_ws winsize)
{
	putstr_fd(info->key.scroll_up, STDIN, where_err(LINE, FILE), info);
	// putstr_fd(info->key.cursor_save, STDIN, where_err(LINE, FILE), info);
	if (winsize.ws_col == info->cursor.cur_pos[X])
		move_specified_position(info->cursor.cur_pos[Y] + 1,
								1, where_err(LINE, FILE), info);
	else if (info->cursor.command_end_pos[Y] == winsize.ws_row)
		move_specified_position(info->cursor.cur_pos[Y] - 1,
								info->cursor.cur_pos[X] + 1, where_err(LINE, FILE), info);
	else
		move_specified_position(info->cursor.cur_pos[Y],
								info->cursor.cur_pos[X] + 1, where_err(LINE, FILE), info);
}

void	display_command(t_string *command, t_minishell *info)
{
	size_t	i;
	t_ws	winsize;

	i = 0;
	// putstr_fd(info->key.cursor_save, STDIN, where_err(LINE, FILE), info);
	while (command->str[i])
	{
		putstr_fd(info->key.clean_right, STDIN, where_err(LINE, FILE), info);
		command->len++;
		winsize = get_window_size(info);
		if (is_right_edge(winsize, info->cursor.cur_pos)
				|| is_right_edge(winsize, info->cursor.command_end_pos))
			scroll_window(info, winsize);
		handle_forward_cursor_pos(info->cursor.cur_pos,
			info->cursor.command_start_pos, info->cursor.command_end_pos, info);
		i++;
	}
	move_specified_position(info->cursor.command_start_pos[Y],
		info->cursor.command_start_pos[X], where_err(LINE, FILE), info);
	// putstr_fd(info->key.cursor_restore, STDIN, where_err(LINE, FILE), info);
	putstr_fd(command->str, STDIN, where_err(LINE, FILE), info);
}

int		get_command_len_from_pos(int pos_end[2], int pos_start[2],
						t_minishell *info)
{
	int	len;
	int max_window_x;

	len = 0;
	max_window_x = get_window_size_x(info);
	if (pos_end[Y] != pos_start[Y])
		len = (pos_end[Y] - pos_start[Y] - 1) * max_window_x +
			pos_end[X] + max_window_x - pos_start[X];
	else
		len = pos_end[X] - pos_start[X];
	return (len);
}

int		get_now_index(t_minishell *info)
{
	int			len;
	int			max_window_x;
	t_cursor	cursor;

	len = 0;
	cursor = info->cursor;
	max_window_x = get_window_size_x(info);
	if (cursor.cur_pos[Y] != cursor.command_start_pos[Y])
		len = (cursor.cur_pos[Y] - cursor.command_start_pos[Y] - 1)
			* max_window_x + cursor.cur_pos[X]
			+ max_window_x - cursor.command_start_pos[X];
	else
		len = cursor.cur_pos[X] - cursor.command_start_pos[X];
	return (len);
}

bool	get_cursor_position(int pos[2], t_minishell *info)
{
	ssize_t			rc;
	unsigned int	i;
	char			*ptr;
	char			buf[32];

	if (write(STDOUT, "\x1b[6n", 4) < 4)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	i = 0;
	while (1)
	{
		if (i == 32)
			return (false);
		rc = read(STDIN, buf + i, 1);
		if (rc == -1)
			all_free_exit(info, ERR_READ, __LINE__, __FILE__);
		if (buf[i] == 'R' || rc == 0)
			break ;
		i++;
	}
	buf[i] = '\0';
	if (buf[0] != '\x1b' || buf[1] != '[')
		return (false);
	pos[Y] = ft_atoi(buf + 2);
	ptr = ft_strchr(buf, ';') + 1;
	if (ptr == NULL)
		return (false);
	pos[X] = ft_atoi(ptr);
	return (true);
}

void	delete_displayed_command(t_err err, t_string *command,
							t_minishell *info)
{
	int		i;
	int		len;

	putstr_fd(info->key.cursor_save, STDIN, err, info);
	move_specified_position(info->cursor.command_end_pos[Y],
		info->cursor.command_end_pos[X], err, info);
	dup_pos(info->cursor.cur_pos, info->cursor.command_end_pos);
	len = get_command_len_from_pos(info->cursor.command_end_pos,
		info->cursor.command_start_pos, info);
	i = -1;
	while (++i < len)
		delete_displayed_char(NULL, command, info);
	putstr_fd(info->key.cursor_restore, STDIN, err, info);
}

void		do_nothing(char *buf, t_string *command, t_minishell *info)
{
	(void)info;
	(void)command;
	(void)buf;
	return ;
}
