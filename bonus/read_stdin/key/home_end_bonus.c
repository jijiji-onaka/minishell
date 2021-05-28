/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home_end_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 03:56:08 by tjinichi          #+#    #+#             */
/*   Updated: 2021/05/25 01:50:51 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bonus_includes/minishell_bonus.h"

void	go_command_beginning(char *buf, t_string *command, t_minishell *info)
{
	(void)buf;
	(void)command;
	info->key.multi_byte_flag = false;
	move_specified_position(info->cursor.command_start_pos[Y],
		info->cursor.command_start_pos[X], where_err(LINE, FILE), info);
	dup_pos(info->cursor.cur_pos, info->cursor.command_start_pos);
}

void	go_command_end(char *buf, t_string *command, t_minishell *info)
{
	(void)buf;
	(void)command;
	info->key.multi_byte_flag_2 = false;
	move_specified_position(info->cursor.command_end_pos[Y],
		info->cursor.command_end_pos[X], where_err(LINE, FILE), info);
	dup_pos(info->cursor.cur_pos, info->cursor.command_end_pos);
}
