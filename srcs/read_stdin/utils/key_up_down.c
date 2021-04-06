/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_up_down.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:50:46 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/06 15:32:20 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	trace_history_up(char *buf, t_string *command, t_minishell *info)
{
	char	*history_command;

	if (info->command_history == NULL)
		return ;
	if (info->command_history->next == NULL)
		info->ptr_for_free = ft_strdup(command->str);
	delete_displayed_command(where_err(LINE, FILE), command, info);
	history_command = ft_strdup(info->command_history->command);
	if (history_command == NULL)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	// if (info->command_history->prev)
	// {
		ptr_free((void**)&(command->str));
		command->str = history_command;
		info->command_history = info->command_history->prev;
	// }
	dup_pos(info->cursor.cur_pos, info->cursor.command_start_pos);
	dup_pos(info->cursor.command_end_pos, info->cursor.cur_pos);
	display_command(command, info);
}

void	trace_history_down(char *buf, t_string *command, t_minishell *info)
{
	char	*history_command;

	if (info->command_history == NULL
		|| info->command_history->next == NULL)
		return ;
	delete_displayed_command(where_err(LINE, FILE), command, info);
	if (info->command_history->next->next == NULL)
	{
		history_command = ft_strdup(info->ptr_for_free);
		free(info->ptr_for_free);
		info->ptr_for_free = NULL;
	}
	else if (info->command_history->next->next != NULL)
	{
		history_command = ft_strdup(info->command_history->next->next->command);
	}
	// else
	// {
	// 	history_command = info->ptr_for_free;
	// 	info->ptr_for_free = NULL;
	// 	info->history_flag = false;
	// }
	ptr_free((void**)&(command->str));
	if (history_command == NULL)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	if (info->command_history->next)
		info->command_history = info->command_history->next;
	command->str = history_command;
	// printf("\n\n=[%s]\n\n", command->str);
	// printf("\n\n=[%s]\n\n", info->ptr_for_free);
	dup_pos(info->cursor.cur_pos, info->cursor.command_start_pos);
	dup_pos(info->cursor.command_end_pos, info->cursor.cur_pos);
	display_command(command, info);
}
