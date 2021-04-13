/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:53:58 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/13 13:01:42 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	create_new_command(t_string *command, char buf, t_err err,
					t_minishell *info)
{
	int		index[3];
	int		len;
	char	*dst;
	int		index_1;

	index_1 = get_now_index(info, command);
	len = command->len + 1;
	dst = safe_malloc(len + 1, err, info);
	index[0] = 0;
	index[1] = 0;
	index[2] = 0;
	while (index[1] < len)
	{
		if (index[1] == index_1)
			dst[index[1]++] = buf;
		else
			dst[index[1]++] = command->str[index[0]++];
	}
	dst[index[1]] = '\0';
	free(command->str);
	command->str = dst;
}

void	print_user_pushed_char(char *buf, t_string *command,
									t_minishell *info)
{
	struct winsize	winsize;
	int				i;

	i = -1;
	while (buf[++i])
	{
		create_new_command(command, buf[i], where_err(LINE, FILE), info);
		putchar_fd(buf[i], STDIN, where_err(LINE, FILE), info);
		winsize = get_window_size(info);
		if (is_right_edge(winsize, info->cursor.cur_pos)
			|| is_right_edge(winsize, info->cursor.command_end_pos))
			scroll_window(info, winsize, buf[i]);
		putstr_fd(info->key.cursor_save, STDIN, where_err(LINE, FILE), info);
		putstr_fd(command->str + get_now_index(info, command) + 1, STDIN,
			where_err(LINE, FILE), info);
		putstr_fd(info->key.cursor_restore, STDIN, where_err(LINE, FILE), info);
		command->len++;
		handle_forward_cursor_pos(info->cursor.cur_pos,
			info->cursor.command_start_pos, info->cursor.command_end_pos, info);
	}
}

void	pushed_newline(char *buf, t_string *command, t_minishell *info)
{
	if (command->str[0] == '\0')
		ptr_free((void **)&(command->str));
	move_specified_position(info->cursor.command_end_pos[Y],
		info->cursor.command_end_pos[X], where_err(LINE, FILE), info);
	if (write(STDOUT, "\n", 1) < 1)
	{
		ptr_free((void **)&(command->str));
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	}
}

void	do_nothing(char *buf, t_string *command, t_minishell *info)
{
	return ;
}
