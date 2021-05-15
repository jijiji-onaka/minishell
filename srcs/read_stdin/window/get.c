/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 11:51:17 by tjinichi          #+#    #+#             */
/*   Updated: 2021/05/07 03:56:01 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	get_from_nl_to_nl(t_string *command, t_cursor cursor, int pos[2])
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
		if (flag == false && command->str[i] == '\n')
			flag = true;
		else if (flag == true && command->str[i] == '\n')
			break ;
		i--;
	}
	if (flag == false)
		res += command->len;
	if (cursor.command_start_pos[Y] == pos[Y] - 1)
		res += cursor.command_start_pos[X];
	return (res);
}

int	get_command_len_from_pos(int pos_end[2], int pos_start[2],
						t_minishell *info)
{
	int	len;
	int	max_window_x;

	len = 0;
	max_window_x = get_window_size(info).ws_col;
	if (pos_end[Y] != pos_start[Y])
		len = (pos_end[Y] - pos_start[Y] - 1) * max_window_x
			+ pos_end[X] + max_window_x - pos_start[X];
	else
		len = pos_end[X] - pos_start[X];
	return (len);
}

int	get_now_index(t_minishell *info, t_string *command)
{
	char	*str;
	int		i;
	int		start_pos[2];
	int		max_window_x;

	str = command->str;
	i = 0;
	dup_pos(start_pos, info->cursor.command_start_pos);
	max_window_x = get_window_size(info).ws_col;
	while (str[i])
	{
		if (equal_pos(start_pos, info->cursor.cur_pos) == true)
			break ;
		if (str[i] == '\n')
			start_pos[X] = max_window_x;
		handle_forward_cursor_pos(start_pos, NULL, NULL, info);
		i++;
	}
	return (i);
}

bool	get_cursor_position(int pos[2], t_minishell *info)
{
	ssize_t			rc;
	unsigned int	i;
	char			*ptr;
	char			buf[33];

	putstr_fd("\x1b[6n", STDOUT, where_err(LINE, FILE), info);
	i = 0;
	while (i < 32)
	{
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

struct winsize	get_window_size(t_minishell *info)
{
	struct winsize	ws;
	int				window_size[2];
	t_err			err;

	if (ioctl(STDOUT, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0)
	{
		err = where_err(LINE, FILE);
		putstr_fd(info->key.cursor_save, STDIN, err, info);
		if (write(STDOUT, "\x1b[999C\x1b[999B", 12) != 12)
			all_free_exit(info, ERR_WRITE, LINE, FILE);
		if (get_cursor_position(window_size, info) == false)
			all_free_exit(info, ERR_GET_WINDOW_SIZE, LINE, FILE);
		putstr_fd(info->key.cursor_restore, STDIN, err, info);
		ws.ws_col = window_size[X];
		ws.ws_row = window_size[Y];
	}
	if (ft_numlen(ws.ws_col) + ft_numlen(ws.ws_row) + 5 >= 32)
	{
		red_error();
		putstr_fd("window size is too large\n", STDERR,
			where_err(LINE, FILE), info);
		all_free_minishell_info(info);
		exit(EXIT_FAILURE);
	}
	return (ws);
}
