/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_left_right_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 05:43:40 by tjinichi          #+#    #+#             */
/*   Updated: 2021/05/25 01:19:02 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bonus_includes/minishell_bonus.h"

void	move_word_directly_to_left(char *buf, t_string *command,
								t_minishell *info)
{
	char	*str;
	size_t	len;
	size_t	i;

	info->key.multi_byte_flag = false;
	if (equal_pos(info->cursor.cur_pos, info->cursor.command_start_pos) == true)
		return ;
	len = get_now_index(info, command);
	str = command->str;
	i = 0;
	while (i < len)
	{
		if (i != 0 && str[len - i] != ' ' && str[len - i - 1] == ' ')
			break ;
		i++;
		move_cursor_left(buf, command, info);
	}
}

void	move_word_directly_to_right(char *buf, t_string *command,
								t_minishell *info)
{
	char	*str;
	size_t	len;
	size_t	i;

	info->key.multi_byte_flag = false;
	if (equal_pos(info->cursor.cur_pos, info->cursor.command_end_pos) == true)
		return ;
	len = get_now_index(info, command);
	str = command->str;
	i = len;
	while (str[i])
	{
		if (i != 0 && i != len && str[i] == ' ' && str[i - 1] != ' ')
			break ;
		i++;
		move_cursor_right(buf, command, info);
	}
}
