/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_home_end.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 03:56:08 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/06 07:39:03 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	go_command_beginning(char *buf, t_string *command, t_minishell *info)
{
	size_t	i;
	size_t	len;
	char	*left;

	len = get_now_index(info);
	left = info->key.left;
	i = 0;
	while (i < len)
	{
		move_cursor_left(buf, command, info);
		i++;
	}
}

void	go_command_end(char *buf, t_string *command, t_minishell *info)
{
	size_t	i;
	size_t	len;
	char	*right;

	i = get_now_index(info);
	right = info->key.right;
	len = get_command_len_from_pos(info->cursor.command_end_pos,
			info->cursor.command_start_pos, info);
	while (i < len)
	{
		move_cursor_right(buf, command, info);
		i++;
	}
}
