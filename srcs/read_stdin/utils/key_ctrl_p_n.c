/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_ctrl_p_n.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 03:17:29 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/04 03:01:09 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// static bool	move_specified_position(int row, int col, int row_len, int col_len)
// {
// 	char	str[row_len + col_len + 5];
// 	uint	i;
// 	uint	total;

// 	str[0] = '\x1b';
// 	str[1] = '[';
// 	i = 1 + row_len;
// 	while (row != 0)
// 	{
// 		str[1 + row_len--] = row % 10 + '0';
// 		row /= 10;
// 	}
// 	str[i++ + 1] = ';';
// 	total = i + col_len + 1;
// 	while (col != 0)
// 	{
// 		str[i + col_len--] = col % 10 + '0';
// 		col /= 10;
// 	}
// 	str[total++] = 'H';
// 	str[total] = '\0';
// 	if (write(STDIN, str, total) == false)
// 		return (false);
// 	return (true);
// }

void		move_up_one_line(char *buf, t_string *command, t_minishell *info)
{
	return ;
	if ((info->window.prompt_len + info->key.save_command_len) <= info->window.ws.ws_col)
		return ;
	// get_cursor_position(&(info->cursor.cur_pos_y), &(info->cursor.cur_pos_x), info);
	// if ((info->window.prompt_len + info->key.save_command_len) / info->window.ws.ws_col == 1
	// && info->window.command_start_col > info->cursor.cur_pos_x)
	// {
	// 	if (info->window.command_start_row == info->window.ws.ws_row)
	// 		move_specified_position(info->window.command_start_row - 1,
	// 			info->window.command_start_col,
	// 			ft_numlen(info->window.command_start_row - 1),
	// 			ft_numlen(info->window.command_start_col));
	// 	else
	// 		move_specified_position(info->window.command_start_row,
	// 			info->window.command_start_col,
	// 			ft_numlen(info->window.command_start_row),
	// 			ft_numlen(info->window.command_start_col));
	// 	command->len = 0;
	// 	return ;
	// }
	if (ft_putstr_fd(info->key.up, STDIN) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	command->len -= info->window.ws.ws_col;
}

void	move_down_one_line(char *buf, t_string *command, t_minishell *info)
{
	return ;
	if ((info->window.prompt_len + info->key.save_command_len) <= info->window.ws.ws_col)
		return ;
	// get_cursor_position(&(info->cursor.cur_pos_y), &(info->cursor.cur_pos_x), info);
	if (command->len + info->window.prompt_len > info->key.save_command_len)
	{
		if (ft_putstr_fd(info->key.down, STDIN) == false)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
		move_direction(info->key.save_command_len + info->window.prompt_len - info->window.ws.ws_col, info->key.left, info);
		command->len = info->key.save_command_len;
		return ;
	}
	if (ft_putstr_fd(info->key.down, STDIN) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	command->len += info->window.ws.ws_col;
}
