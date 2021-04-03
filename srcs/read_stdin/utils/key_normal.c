/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_normal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:53:58 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/04 01:45:11 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	edit_displayed_char(char *buf, t_string *command, t_minishell *info)
{
	char	*new;
	size_t	i;
	size_t	j;

	new = malloc(sizeof(char) * (ft_strlen(command->str) + 2));
	if (new == NULL)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	i = 0;
	j = 0;
	while (command->str[i])
	{
		if (j != command->len)
			new[j++] = command->str[i++];
		else
			new[j++] = buf[0];
	}
	new[j] = '\0';
	info->key.save_command_len = j;
	free(command->str);
	command->str = new;
}

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
// 	if (write(STDIN_FILENO, str, total) == false)
// 		return (false);
// 	return (true);
// }

static void	create_new_command(t_string *command, char *buf, t_minishell *info)
{
	size_t	index[3];
	size_t	len;
	char	*dst;

	len = info->key.save_command_len + ft_strlen(buf);
	// if (command->len == 0)
	// 	len++;
	dst = malloc(len + 1);
	if (dst == NULL)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
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
}

void		print_user_pushed_char(char *buf, t_string *command,
									t_minishell *info)
{
	// printf("\n1 = %d\n", info->cursor.command_end_pos[Y] );
	// 	printf("2 = %d\n", info->cursor.command_end_pos[X] );
	// 	printf("2 = %d\n", info->cursor.cur_pos[Y] );
	// 	printf("2 = %d\n", info->cursor.cur_pos[X] );
	create_new_command(command, buf, info);
	if (ft_putstr_fd(buf, STDOUT_FILENO) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	command->len++;
	info->cursor.cur_pos[X]++;
	info->cursor.command_end_pos[X]++;
	if (info->window.ws.ws_col + 1 == info->cursor.command_end_pos[X])
	{
		if (info->cursor.command_end_pos[X] != info->cursor.cur_pos[X])
			if (ft_putstr_fd(info->key.scroll_up, STDOUT_FILENO) == false)
				all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
		if (info->window.ws.ws_row != info->cursor.command_end_pos[Y])
			info->cursor.command_end_pos[Y]++;
		if (info->cursor.command_start_pos[Y] != UPPER_EDGE)
			info->cursor.command_start_pos[Y]--;
		info->cursor.command_end_pos[X] = LEFT_EDGE;
	}
	if (info->window.ws.ws_col + 1 == info->cursor.cur_pos[X])
	{
		if (ft_putstr_fd(info->key.scroll_up, STDOUT_FILENO) == false)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
		if (info->window.ws.ws_row != info->cursor.cur_pos[Y])
			info->cursor.cur_pos[Y]++;
		if (info->cursor.command_start_pos[Y] != UPPER_EDGE)
			info->cursor.command_start_pos[Y]--;
		info->cursor.cur_pos[X] = LEFT_EDGE;
		move_specified_position(info->cursor.cur_pos[Y], 0,
			numlen(info->cursor.cur_pos[Y], info->window, Y), 1);
	}
	if (ft_putstr_fd(info->key.save, STDIN_FILENO) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (ft_putstr_fd(command->str + command->len, STDOUT_FILENO) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (ft_putstr_fd(info->key.reset, STDIN_FILENO) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
}

void		pushed_newline(char *buf, t_string *command, t_minishell *info)
{
	if (command->str[0] == '\0')
		ptr_free((void**)&(command->str));
	if (info->cursor.cur_pos[X] == LEFT_EDGE)
		;
	else if (write(STDOUT_FILENO, "\n", 1) < 1)
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
