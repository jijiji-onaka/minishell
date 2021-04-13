/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 05:24:40 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/13 14:03:24 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bonus_includes/minishell_bonus.h"

bool	is_win_bottom_right_edge(struct winsize winsize, int pos[2])
{
	if (pos == NULL)
		return (false);
	if (winsize.ws_col == pos[X] && winsize.ws_row == pos[Y])
		return (true);
	return (false);
}

bool	is_win_bottom_edge(struct winsize winsize, int pos[2])
{
	if (pos == NULL)
		return (false);
	if (winsize.ws_row == pos[Y])
		return (true);
	return (false);
}

bool	is_right_edge(struct winsize winsize, int pos[2])
{
	if (pos == NULL)
		return (false);
	if (winsize.ws_col == pos[X])
		return (true);
	return (false);
}

void	handle_forward_cursor_pos(int pos[2],
			int start_pos[2], int end_pos[2], t_minishell *info)
{
	struct winsize	winsize;

	winsize = get_window_size(info);
	if (is_right_edge(winsize, end_pos))
	{
		if (is_win_bottom_edge(winsize, end_pos))
		{
			pos[Y] = signed_max(0, pos[Y] - 1);
			start_pos[Y] = signed_max(0, start_pos[Y] - 1);
		}
		end_pos[Y] = signed_min(winsize.ws_row, end_pos[Y] + 1);
		end_pos[X] = LEFT_EDGE;
	}
	else if (end_pos)
		end_pos[X]++;
	if (is_right_edge(winsize, pos))
	{
		pos[X] = LEFT_EDGE;
		pos[Y] = signed_min(winsize.ws_row, pos[Y] + 1);
	}
	else if (pos)
		pos[X]++;
}

void	handle_back_cursor_pos(t_string *command, int pos[2],
						t_minishell *info, int window_max_x)
{
	if (pos[X] == LEFT_EDGE)
	{
		pos[X] = signed_min(get_from_nl_to_nl(command, info->cursor, pos),
				window_max_x);
		if (pos[Y] != UPPER_EDGE)
			--pos[Y];
	}
	else
		--pos[X];
}
