/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_del_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:51:59 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/03 18:29:38 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void		clear_terminal(char *buf, t_string *command, t_minishell *info)
{
	(void)buf;
	ft_putstr_fd(info->key.clean, STDOUT_FILENO);
	put_prompt(info);
	ft_putstr_fd(command->str, STDOUT_FILENO);
}

static void	create_new_command(t_string *command, t_minishell *info)
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
	// printf("%zd\n", len);
	while (str[i])
	{
		if (i != len)
			str[j++] = str[i];
		i++;
	}
	command->str[j] = '\0';
	info->key.save_command_len = j;
}

static void	delete_when_multiple_line(char *buf, t_string *command,
					t_minishell *info)
{
	if (ft_putstr_fd(info->key.left, STDIN_FILENO) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (ft_putstr_fd(info->key.save, STDIN_FILENO) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (ft_putstr_fd(info->key.clean_right, STDIN_FILENO) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	moving(info->window.ws.ws_col, info->key.right, info);
	if (ft_putstr_fd(info->key.up, STDIN_FILENO) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (ft_putstr_fd(info->key.save, STDIN_FILENO) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (ft_putstr_fd(info->key.clean_right, STDIN_FILENO) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	ft_putstr_fd(command->str + command->len, STDOUT_FILENO);
	--command->len;
	create_new_command(command, info);
	ft_putstr_fd(info->key.reset, STDIN_FILENO);
	if (ft_putstr_fd(info->key.right, STDIN_FILENO) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	// --info->window.line_num;
	return ;
}

static bool	go_to_position(int row, int col, int row_len, int col_len)
{
	char	str[row_len + col_len + 5];
	uint	i;
	uint	total;

	str[0] = '\x1b';
	str[1] = '[';
	i = 1 + row_len;
	while (row != 0)
	{
		str[1 + row_len--] = row % 10 + '0';
		row /= 10;
	}
	str[i++ + 1] = ';';
	total = i + col_len + 1;
	while (col != 0)
	{
		str[i + col_len--] = col % 10 + '0';
		col /= 10;
	}
	str[total++] = 'H';
	str[total] = '\0';
	if (write(STDIN_FILENO, str, total) == false)
		return (false);
	return (true);
}

void		delete_displayed_char(char *buf, t_string *command,
					t_minishell *info)
{
	if (command->len == 0)
		return ;
	if ((info->window.prompt_len + command->len) % info->window.ws.ws_col == 0)
		return (delete_when_multiple_line(buf, command, info));
	if (ft_putstr_fd(info->key.left, STDIN_FILENO) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (ft_putstr_fd(info->key.save, STDIN_FILENO) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (ft_putstr_fd(info->key.clean_right, STDIN_FILENO) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	ft_putstr_fd(command->str + command->len, STDOUT_FILENO);
	create_new_command(command, info);
	if (ft_putstr_fd(info->key.reset, STDIN_FILENO) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	// if ((info->window.prompt_len + command->len) < info->key.save_command_len)
	// {
	// 	get_cursor_position(&(info->window.cur_pos_y), &(info->window.cur_pos_x), info);
	// 	go_to_position(info->window.cur_pos_y + (info->key.save_command_len + info->window.prompt_len) / info->window.ws.ws_col,
	// 	(info->key.save_command_len + info->window.prompt_len) % info->window.ws.ws_col + 1
	// 	, ft_numlen(info->window.cur_pos_y + (info->key.save_command_len + info->window.prompt_len) / info->window.ws.ws_col),
	// 	ft_numlen((info->key.save_command_len + info->window.prompt_len) % info->window.ws.ws_col + 1));
	// 	if (ft_putstr_fd(info->key.left, STDIN_FILENO) == false)
	// 		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	// 	if (ft_putstr_fd(info->key.save, STDIN_FILENO) == false)
	// 		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	// 	if (ft_putstr_fd(info->key.clean_right, STDIN_FILENO) == false)
	// 		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	// if (ft_putstr_fd(info->key.reset, STDIN_FILENO) == false)
	// 	all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	// 	go_to_position(info->window.cur_pos_y, info->window.cur_pos_x, ft_numlen(info->window.cur_pos_y), ft_numlen(info->window.cur_pos_x));
	// }
	--command->len;
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
