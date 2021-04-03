/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_normal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:53:58 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/03 18:40:02 by tjinichi         ###   ########.fr       */
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

void		print_user_pushed_char(char *buf, t_string *command,
									t_minishell *info)
{
	// if ((info->window.prompt_len + command->len) % info->window.ws.ws_col == 0)
	// 	++info->window.line_num;
	// ft_putstr_fd(tgetstr("im", NULL), 1);
	// ft_putstr_fd(tgetstr("ic", NULL), 1);
	if (info->key.save_command_len == command->len)
	{
		command->len++;
		info->key.save_command_len = command->len;
		info->window.cur_pos[X]++;
		info->window.command_end_pos[X]++;
		// printf("%d\n", info->window.cur_pos[X]);
		// printf("%d\n", info->window.ws.ws_col);
		if (ft_putstr_fd(buf, STDOUT_FILENO) == false)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
		if (info->window.ws.ws_col + 1 == info->window.cur_pos[X])
			ft_putstr_fd(tgetstr("do", NULL), 1);
		if (!(command->str = re_strjoin(&(command->str), command->str, buf)))
			all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
		return ;
	}
	if (ft_putstr_fd(info->key.save, STDIN_FILENO) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (ft_putstr_fd(info->key.clean_right, STDIN_FILENO) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	edit_displayed_char(buf, command, info);
	if ((info->window.prompt_len + command->len + 1) % info->window.ws.ws_col == 0)
		if (write(STDOUT_FILENO, "\n", 1) < 1)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	ft_putstr_fd(command->str + command->len, STDOUT_FILENO);
	ft_putstr_fd(info->key.reset, STDIN_FILENO);
	ft_putstr_fd(buf, STDOUT_FILENO);
	// ft_putstr_fd(tgetstr("ip", NULL), 1);
	// ft_putstr_fd(tgetstr("ei", NULL), 1);
	command->len++;
}

void		pushed_newline(char *buf, t_string *command, t_minishell *info)
{
	int i = 0;
	while (i < (info->key.save_command_len + info->window.prompt_len) / info->window.ws.ws_col + 1)
	{
		if (write(STDOUT_FILENO, "\n", 1) < 1)
		{
			ptr_free((void **)&(command->str));
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
		}
		i++;
	}
	if (command->str[0] == '\0')
		ptr_free((void**)&(command->str));
}

void		do_nothing(char *buf, t_string *command, t_minishell *info)
{
	(void)info;
	(void)command;
	(void)buf;
	return ;
}
