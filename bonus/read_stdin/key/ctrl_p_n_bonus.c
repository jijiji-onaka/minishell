/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_p_n_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 03:17:29 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/13 14:03:24 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bonus_includes/minishell_bonus.h"

void	move_up_one_line(char *buf, t_string *command, t_minishell *info)
{
	(void)buf;
	(void)command;
	if (info->cursor.cur_pos[Y] == info->cursor.command_start_pos[Y])
		return ;
	if (info->cursor.cur_pos[Y] - info->cursor.command_start_pos[Y] == 1
		&& info->cursor.cur_pos[X] < info->cursor.command_start_pos[X])
	{
		move_specified_position(info->cursor.command_start_pos[Y],
			info->cursor.command_start_pos[X], where_err(LINE, FILE), info);
		dup_pos(info->cursor.cur_pos, info->cursor.command_start_pos);
	}
	else
	{
		--info->cursor.cur_pos[Y];
		move_specified_position(info->cursor.cur_pos[Y],
			info->cursor.cur_pos[X], where_err(LINE, FILE), info);
	}
}

void	move_down_one_line(char *buf, t_string *command, t_minishell *info)
{
	(void)buf;
	(void)command;
	if (info->cursor.cur_pos[Y] == info->cursor.command_end_pos[Y])
		return ;
	if (info->cursor.command_end_pos[Y] - info->cursor.cur_pos[Y] == 1
		&& info->cursor.command_end_pos[X] < info->cursor.cur_pos[X])
	{
		move_specified_position(info->cursor.command_end_pos[Y],
			info->cursor.command_end_pos[X], where_err(LINE, FILE), info);
		dup_pos(info->cursor.cur_pos, info->cursor.command_end_pos);
	}
	else
	{
		++info->cursor.cur_pos[Y];
		move_specified_position(info->cursor.cur_pos[Y],
			info->cursor.cur_pos[X], where_err(LINE, FILE), info);
	}
}
