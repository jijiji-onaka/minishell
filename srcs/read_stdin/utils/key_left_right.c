/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_left_right.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:49:37 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/02 22:05:06 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	moving(size_t len, char *move_direction, t_minishell *info)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (ft_putstr_fd(move_direction, STDIN_FILENO) == false)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
		i++;
	}
}

void	move_cursor_left(char *buf, t_string *command, t_minishell *info)
{
	if (command->len == 0)
		return ;
	--command->len;
	moving(1, info->key.left, info);
	// ft_putstr_fd(info->key.left, STDIN_FILENO);
}

void	move_cursor_right(char *buf, t_string *command, t_minishell *info)
{
	if (command->len == info->key.save_command_len)
		return ;
	++command->len;
	moving(1, info->key.right, info);
	// ft_putstr_fd(info->key.right, STDIN_FILENO);
}

void	move_left_directly_word_toward(char *buf, t_string *command,
								t_minishell *info)
{
	char	*str;
	size_t	len;
	size_t	i;
	char	*left;

	info->key.ctrl_lr_flag = false;
	if (command->len == 0)
		return;
	len = command->len;
	str = command->str;
	i = 0;
	left = info->key.left;
	while (i < len)
	{
		if (i != 0 && str[len - i] != ' ' && str[len - i - 1] == ' ')
			break;
		i++;
		if (ft_putstr_fd(left, STDIN_FILENO) == false)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	}
	command->len -= i;
}

void	move_right_directly_word_toward(char *buf, t_string *command,
								t_minishell *info)
{
	char	*str;
	size_t	len;
	size_t	i;
	char	*right;

	info->key.ctrl_lr_flag = false;
	if (command->len == info->key.save_command_len)
		return ;
	len = command->len;
	str = command->str;
	i = len;
	right = info->key.right;
	while (str[i])
	{
		if (i != 0 && i != len && str[i] == ' ' && str[i - 1] != ' ')
			break;
		i++;
		if (ft_putstr_fd(right, STDIN_FILENO) == false)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	}
	command->len = i;
}
