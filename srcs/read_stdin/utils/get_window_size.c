/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_window_size.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 00:11:50 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/06 05:01:47 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static bool	failed_get_winsize(int window_size[2], t_minishell *info)
{
	if (ft_putstr_fd(info->key.cursor_save, STDIN) == false)
		return (false);
	if (write(STDOUT, "\x1b[999C\x1b[999B", 12) != 12)
		return (false);
	if (get_cursor_position(window_size, info) == false)
		return (false);
	if (ft_putstr_fd(info->key.cursor_restore, STDIN) == false)
		return (false);
	return (true);
}

t_ws		get_window_size(t_minishell *info)
{
	t_ws	ws;
	int		window_size[2];

	if (ioctl(STDOUT, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0)
	{
		if (failed_get_winsize(window_size, info) == false)
			all_free_exit(info, ERR_GET_WINDOW_SIZE, LINE, FILE);
		ws.ws_col = window_size[X];
		ws.ws_row = window_size[Y];
	}
	return (ws);
}

int			get_window_size_x(t_minishell *info)
{
	return (get_window_size(info).ws_col);
}

int			get_window_size_y(t_minishell *info)
{
	return (get_window_size(info).ws_row);
}
