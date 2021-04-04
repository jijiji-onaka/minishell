/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:51:59 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/04 06:05:40 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	clear_terminal(char *buf, t_string *command, t_minishell *info)
{

	(void)buf;
	putstr_fd(info->key.clean, STDOUT, where_err(LINE, FILE), info);
	put_prompt(info);
	dup_pos(info->cursor.cur_pos, info->cursor.command_start_pos);
	dup_pos(info->cursor.command_end_pos, info->cursor.command_start_pos);
	display_command(command, info);
}
