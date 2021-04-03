/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 23:22:47 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/04 03:26:06 by tjinichi         ###   ########.fr       */
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

int		numlen(int num, t_window window, int x_y)
{
	if (num >= 0 && num < 10)
		return (1);
	else if (num >= 10 && num < 100)
		return (2);
	else if (num >= 100 && num < 1000)
		return (3);
	if (x_y == X)
		return (window.ws.ws_col);
	else if (x_y == Y || true)
		return (window.ws.ws_row);
}

bool	move_specified_position(int pos_y, int pos_x, int y_len, int x_len)
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

void	dup_pos(int src[2], int dst[2])
{
	src[X] = dst[X];
	src[Y] = dst[Y];
}
