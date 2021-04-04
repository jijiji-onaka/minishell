/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_normal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:53:58 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/04 10:03:31 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	create_new_command(t_string *command, char *buf, t_err err,
					t_minishell *info)
{
	size_t	index[3];
	size_t	len;
	char	*dst;

	len = info->key.save_command_len + ft_strlen(buf);
	dst = malloc(len + 1);
	info->ptr_for_free = command->str;
	if (dst == NULL)
		all_free_exit(info, ERR_MALLOC, err.line, err.file);
	index[0] = 0;
	index[1] = 0;
	index[2] = 0;
	while (index[1] < len)
	{
		if (index[1] == command->len)
			while (buf[index[2]])
				dst[index[1]++] = buf[index[2]++];
		else
			dst[index[1]++] = command->str[index[0]++];
	}
	dst[index[1]] = '\0';
	info->key.save_command_len = len;
	free(command->str);
	command->str = dst;
	info->ptr_for_free = NULL;
}

void		print_user_pushed_char(char *buf, t_string *command,
									t_minishell *info)
{
	// printf("\n1 [%d]\n", info->cursor.cur_pos[X]);
	// printf("2 [%d]\n", info->cursor.cur_pos[Y]);
	// printf("3 [%d]\n", info->cursor.command_start_pos[X]);
	// printf("4 [%d]\n", info->cursor.command_start_pos[Y]);
	create_new_command(command, buf, where_err(LINE, FILE), info);
	putstr_fd(buf, STDIN, where_err(LINE, FILE), info);
	command->len++;
	info->key.save_command_len++;
	info->cursor.cur_pos[X]++;
	info->cursor.command_end_pos[X]++;
	if (info->window.ws.ws_col + 1 == info->cursor.command_end_pos[X])
		handle_forward_cursor_pos(info->cursor.command_end_pos,
			NULL, info->window.ws.ws_row);
	if (info->window.ws.ws_col + 1 == info->cursor.cur_pos[X])
	{
		putstr_fd(info->key.scroll_up, STDIN, where_err(LINE, FILE), info);
		handle_forward_cursor_pos(info->cursor.cur_pos,
			info->cursor.command_start_pos, info->window.ws.ws_row);
		move_specified_position(info->cursor.cur_pos[Y], 1,
			where_err(LINE, FILE), info);
	}
	putstr_fd(info->key.save, STDIN, where_err(LINE, FILE), info);
	putstr_fd(command->str + command->len, STDIN, where_err(LINE, FILE), info);
	putstr_fd(info->key.restore, STDIN, where_err(LINE, FILE), info);
}

void		pushed_newline(char *buf, t_string *command, t_minishell *info)
{
	if (command->str[0] == '\0')
		ptr_free((void**)&(command->str));
	if (info->cursor.cur_pos[X] == LEFT_EDGE)
		;
	else if (write(STDOUT, "\n", 1) < 1)
	{
		ptr_free((void **)&(command->str));
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	}
}

void		do_nothing(char *buf, t_string *command, t_minishell *info)
{
	(void)info;
	(void)command;
	(void)buf;
	return ;
}
