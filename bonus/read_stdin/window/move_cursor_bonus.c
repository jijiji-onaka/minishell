/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 11:47:18 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/13 14:03:24 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bonus_includes/minishell_bonus.h"

static int	numlen(int num, struct winsize winsize, int x_y)
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

static bool	move_specified_position_main(int pos_y, int pos_x,
							int y_len, int x_len)
{
	char	str[32];
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
	int				y_len;
	int				x_len;
	struct winsize	winsize;

	winsize = get_window_size(info);
	y_len = numlen(pos_y, winsize, Y);
	x_len = numlen(pos_x, winsize, X);
	if (move_specified_position_main(pos_y, pos_x, y_len, x_len) == false)
		all_free_exit(info, ERR_WRITE, err.line, err.file);
}
