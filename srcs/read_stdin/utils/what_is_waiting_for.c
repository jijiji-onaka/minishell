/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   what_is_waiting_for.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 21:36:06 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/09 11:46:44 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void		display_what_is_waiting_for(char chr, char **ptr1, char **ptr2,
					t_minishell *info)
{
	int		write_num;

	write_num = 1;
	if (chr == '\"')
		write_num = write(STDOUT, "wait :(double quote)> ", 22);
	else if (chr == '\'')
		write_num = write(STDOUT, "wait :(single quote)> ", 22);
	else
		write_num = write(STDOUT, "wait :(normal command)> ", 24);
	if (write_num < 0)
	{
		if (ptr1)
			ptr_free((void**)ptr1);
		if (ptr2)
			ptr_free((void**)ptr2);
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	}
	get_cursor_position(info->cursor.command_start_pos, info);
	dup_pos(info->cursor.cur_pos, info->cursor.command_start_pos);
	dup_pos(info->cursor.command_end_pos, info->cursor.command_start_pos);
}
