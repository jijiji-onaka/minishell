/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_select_target.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 21:54:06 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/02 23:08:50 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	print_user_selected_target(size_t target_start, size_t target_end,
			char *command, t_minishell *info)
{
	size_t	i;

	if (ft_putstr_fd(info->key.color_change, STDIN_FILENO) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	i = target_start;
	while (i < target_end)
		if (ft_putchar_fd(command[i++], STDIN_FILENO) == false)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (ft_putstr_fd(info->key.color_reset, STDIN_FILENO) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	i = target_end;
	while (i < info->key.save_command_len)
		if (ft_putchar_fd(command[i++], STDIN_FILENO) == false)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
}

void		select_target_left(char *buf, t_string *command, t_minishell *info)
{
	size_t	i;

	if (command->len == 0 || info->key.target_start == 0)
		return ;
	if (info->key.target_end == -1 || info->key.target_start == -1)
	{
		info->key.target_end = command->len;
		info->key.target_start = command->len - 1;
	}
	else
		--info->key.target_start;
	moving(command->len - info->key.target_start, info->key.left, info);
	if (ft_putstr_fd(info->key.save, STDIN_FILENO) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (ft_putstr_fd(info->key.reset, STDIN_FILENO) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	print_user_selected_target(info->key.target_start,
		info->key.target_end, command->str, info);
	moving(info->key.save_command_len - info->key.target_end,
		info->key.left, info);
}

void		select_target_right(char *buf, t_string *command, t_minishell *info)
{
	size_t	i;

	if (command->len == info->key.save_command_len ||
		info->key.target_end == info->key.save_command_len)
		return ;
	if (ft_putstr_fd(info->key.cursor_visible, STDIN_FILENO) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (info->key.target_end == -1 || info->key.target_start == -1)
	{
		if (ft_putstr_fd(info->key.cursor_invisible, STDIN_FILENO) == false)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
		info->key.target_start = command->len;
		info->key.target_end = command->len + 1;
	}
	else
		++info->key.target_end;
	moving(info->key.save_command_len - command->len,
		info->key.right, info);
	delete_displayed_command(info->key.save_command_len,
		info->key.left, info->key.clean_right);
	print_user_selected_target(info->key.target_start,
		info->key.target_end, command->str, info);
	moving(info->key.save_command_len - info->key.target_start,
		info->key.left, info);
}
