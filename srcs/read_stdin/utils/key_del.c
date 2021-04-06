/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_del.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 01:48:20 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/06 11:55:18 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	edit_command(t_string *command, t_minishell *info)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*str;

	i = 0;
	j = 0;
	str = command->str;
	len = get_now_index(info) - 1;
	// if (command->len == 0)
	// 	len = 0;
	// else
	// 	len = command->len - 1;
	while (str[i])
	{
		if (i != len)
			str[j++] = str[i];
		i++;
	}
	command->str[j] = '\0';
	// printf("%s\n", command->str);
	// info->key.save_command_len = j;
}

static void	erase_under_line(t_minishell *info, t_err err)
{
	putstr_fd(info->key.cursor_save, STDIN, err, info);
	move_specified_position(info->cursor.command_end_pos[Y],
		info->cursor.command_end_pos[X], where_err(LINE, FILE), info);
	putstr_fd(info->key.delete_line, STDIN, err, info);
	putstr_fd(info->key.cursor_restore, STDIN, err, info);
}

static void	move_right_end_of_line_above(t_minishell *info, t_err err)
{
	putstr_fd(info->key.cursor_save, STDIN, err, info);
	move_specified_position(info->cursor.command_end_pos[Y],
		info->cursor.command_end_pos[X], where_err(LINE, FILE), info);
	putstr_fd(info->key.delete_line, STDIN, err, info);
	putstr_fd(info->key.cursor_restore, STDIN, err, info);
}

void		delete_displayed_char(char *buf, t_string *command,
					t_minishell *info)
{
	int	winsize_x;

	winsize_x = get_window_size_x(info);
	// printf("\n[%d]\n", info->cursor.cur_pos[X]);
	// printf("[%d]\n", info->cursor.cur_pos[Y]);
	if (equal_pos(info->cursor.cur_pos, info->cursor.command_start_pos) == true)
		return ;
	if (info->cursor.command_end_pos[Y] != info->cursor.cur_pos[Y]
		|| info->cursor.cur_pos[X] == LEFT_EDGE)
		erase_under_line(info, where_err(LINE, FILE));
	if (info->cursor.command_start_pos[Y] != info->cursor.cur_pos[Y]
		&& (info->cursor.cur_pos[X] == LEFT_EDGE))
		move_specified_position(info->cursor.cur_pos[Y] - 1,
			winsize_x , where_err(LINE, FILE), info);
	else
		putstr_fd(info->key.left, STDIN, where_err(LINE, FILE), info);
	putstr_fd(info->key.cursor_save, STDIN, where_err(LINE, FILE), info);
	putstr_fd(info->key.clean_right, STDIN, where_err(LINE, FILE), info);
	putstr_fd(command->str + get_now_index(info),
		STDIN, where_err(LINE, FILE), info);
	edit_command(command, info);
	putstr_fd(info->key.cursor_restore, STDIN, where_err(LINE, FILE), info);
	--command->len;
	handle_back_cursor_pos(info->cursor.cur_pos, winsize_x);
	handle_back_cursor_pos(info->cursor.command_end_pos, winsize_x);
}

// bool		delete_displayed_command(size_t len, char *left, char *clean_right)
// {
// 	int	i;

// 	i = 0;
// 	while (i < len)
// 	{
// 		if (ft_putstr_fd(left, STDIN) == false)
// 			return (false);
// 		i++;
// 	}
// 	if (ft_putstr_fd(clean_right, STDIN) == false)
// 		return (false);
// 	return (true);
// }
