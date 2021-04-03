/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_del.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 01:48:20 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/04 02:02:32 by tjinichi         ###   ########.fr       */
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
	if (command->len == 0)
		len = 0;
	else
		len = command->len - 1;
	while (str[i])
	{
		if (i != len)
			str[j++] = str[i];
		i++;
	}
	command->str[j] = '\0';
	info->key.save_command_len = j;
}

static void	erase_line(t_minishell *info)
{
	if (ft_putstr_fd(info->key.save, STDIN_FILENO) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	move_specified_position(info->cursor.command_end_pos[Y],
				info->cursor.command_end_pos[X],
				numlen(info->cursor.cur_pos[Y], info->window, Y),
				numlen(info->cursor.command_end_pos[X], info->window, X));
	if (ft_putstr_fd(info->key.delete_line, STDIN_FILENO) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (ft_putstr_fd(info->key.reset, STDIN_FILENO) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
}

static void	move_right_end_(t_minishell *info)
{
	if (ft_putstr_fd(info->key.save, STDIN_FILENO) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	move_specified_position(info->cursor.command_end_pos[Y],
				info->cursor.command_end_pos[X],
				numlen(info->cursor.cur_pos[Y], info->window, Y),
				numlen(info->cursor.command_end_pos[X], info->window, X));
	if (ft_putstr_fd(info->key.delete_line, STDIN_FILENO) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (ft_putstr_fd(info->key.reset, STDIN_FILENO) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
}

void		delete_displayed_char(char *buf, t_string *command,
					t_minishell *info)
{
	if (command->len == 0)
		return ;
	if (info->cursor.command_end_pos[Y] != info->cursor.cur_pos[Y]
		|| info->cursor.cur_pos[X] == LEFT_EDGE)
		erase_line(info);
	if (info->cursor.command_start_pos[Y] != info->cursor.cur_pos[Y]
		&& (info->cursor.cur_pos[X] == LEFT_EDGE))
	{
		move_specified_position(info->cursor.cur_pos[Y] - 1,
			info->window.ws.ws_col ,
			numlen(info->cursor.cur_pos[Y] - 1, info->window, Y),
			numlen(info->window.ws.ws_col, info->window, X));
	}
	else if (ft_putstr_fd(info->key.left, STDIN_FILENO) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (ft_putstr_fd(info->key.save, STDIN_FILENO) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (ft_putstr_fd(info->key.clean_right, STDIN_FILENO) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	ft_putstr_fd(command->str + command->len, STDOUT_FILENO);
	edit_command(command, info);
	if (ft_putstr_fd(info->key.reset, STDIN_FILENO) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	--command->len;
	if (info->cursor.cur_pos[X] == LEFT_EDGE)
	{
		info->cursor.cur_pos[X] = info->window.ws.ws_col;
		if (info->cursor.cur_pos[Y] != UPPER_EDGE)
			--info->cursor.cur_pos[Y];
	}
	else
		--info->cursor.cur_pos[X];
	if (info->cursor.command_end_pos[X] == LEFT_EDGE)
	{
		info->cursor.command_end_pos[X] = info->window.ws.ws_col;
		if (info->cursor.command_end_pos[Y] != UPPER_EDGE)
			--info->cursor.command_end_pos[Y];
	}
	else
		--info->cursor.command_end_pos[X];
}

bool		delete_displayed_command(size_t len, char *left, char *clean_right)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (ft_putstr_fd(left, STDIN_FILENO) == false)
			return (false);
		i++;
	}
	if (ft_putstr_fd(clean_right, STDIN_FILENO) == false)
		return (false);
	return (true);
}
