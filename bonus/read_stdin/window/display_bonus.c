/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 11:52:39 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/13 14:03:24 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bonus_includes/minishell_bonus.h"

void	scroll_window(t_minishell *info, struct winsize winsize, char now_chr)
{
	putstr_fd(info->key.scroll_up, STDIN, where_err(LINE, FILE), info);
	if (winsize.ws_col == info->cursor.cur_pos[X] || now_chr == '\n')
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
	size_t			i;
	struct winsize	winsize;

	i = 0;
	while (command->str[i])
	{
		putstr_fd(info->key.clean_right, STDIN, where_err(LINE, FILE), info);
		command->len++;
		winsize = get_window_size(info);
		if (is_right_edge(winsize, info->cursor.cur_pos)
			|| is_right_edge(winsize, info->cursor.command_end_pos)
			|| command->str[i] == '\n')
			scroll_window(info, winsize, command->str[i]);
		if (command->str[i] == '\n')
		{
			info->cursor.cur_pos[X] = winsize.ws_col;
			info->cursor.command_end_pos[X] = winsize.ws_col;
		}
		handle_forward_cursor_pos(info->cursor.cur_pos,
			info->cursor.command_start_pos, info->cursor.command_end_pos, info);
		i++;
	}
	move_specified_position(info->cursor.command_start_pos[Y],
		info->cursor.command_start_pos[X], where_err(LINE, FILE), info);
	putstr_fd(command->str, STDIN, where_err(LINE, FILE), info);
}

void	delete_displayed_command(t_err err, t_string *command,
							t_minishell *info)
{
	int		i;
	int		len;

	(void)command;
	move_specified_position(info->cursor.command_end_pos[Y],
		info->cursor.command_end_pos[X], err, info);
	dup_pos(info->cursor.cur_pos, info->cursor.command_end_pos);
	len = command->len;
	i = -1;
	while (++i < len)
	{
		move_cursor_left(NULL, command, info);
		putstr_fd(info->key.clean_right, STDIN, err, info);
		command->len--;
	}
	move_specified_position(info->cursor.command_start_pos[Y],
		info->cursor.command_start_pos[X], err, info);
}
