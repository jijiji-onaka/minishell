/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_up_down.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:50:46 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/29 17:59:18 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	trace_history_up(char *buf, t_string *command, t_minishell *info)
{
	char	*history_command;

	if (info->command_history == NULL)
		return ;
	if (delete_displayed_command(command->len, info->key.left,
			info->key.clean_right) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	history_command = ft_strdup(info->command_history->command);
	if (history_command == NULL)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	if (info->command_history->prev)
		info->command_history = info->command_history->prev;
	if (info->history_flag == false)
	{
		info->ptr_for_free = command->str;
		info->history_flag = true;
	}
	else
		ptr_free((void**)&(command->str));
	if (ft_putstr_fd(history_command, STDOUT_FILENO) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	command->str = history_command;
	command->len = ft_strlen(history_command);
	info->key.save_command_len = command->len;
}

void	trace_history_down(char *buf, t_string *command, t_minishell *info)
{
	char	*history_command;

	if (info->command_history == NULL || (info->history_flag == false && info->command_history->next == NULL))
		return ;
	if (delete_displayed_command(command->len, info->key.left,
			info->key.clean_right) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (info->command_history->next != NULL)
		history_command = ft_strdup(info->command_history->next->command);
	else
	{
		history_command = info->ptr_for_free;
		info->ptr_for_free = NULL;
		info->history_flag = false;
	}
	if (history_command == NULL)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	if (info->command_history->next)
		info->command_history = info->command_history->next;
	ptr_free((void**)&(command->str));
	if (ft_putstr_fd(history_command, STDOUT_FILENO) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	command->str = history_command;
	command->len = ft_strlen(history_command);
	info->key.save_command_len = command->len;
}
