/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   up_down.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:50:46 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/22 18:20:51 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	trace_history_up(char *buf, t_string *command, t_minishell *info)
{
	(void)buf;
	if (info->history.list->old_hist == NULL)
		return ;
	delete_displayed_command(where_err(LINE, FILE), command, info);
	free(info->history.list->command);
	info->history.list->command = command->str;
	info->history.list = info->history.list->old_hist;
	command->str = ft_strdup(info->history.list->command);
	if (command->str == NULL)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	dup_pos(info->cursor.cur_pos, info->cursor.command_start_pos);
	dup_pos(info->cursor.command_end_pos, info->cursor.cur_pos);
	command->len = 0;
	display_command(command, info);
}

void	trace_history_down(char *buf, t_string *command, t_minishell *info)
{
	(void)buf;
	if (info->history.list->new_hist == NULL)
		return ;
	delete_displayed_command(where_err(LINE, FILE), command, info);
	free(info->history.list->command);
	info->history.list->command = command->str;
	info->history.list = info->history.list->new_hist;
	command->str = ft_strdup(info->history.list->command);
	if (command->str == NULL)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	dup_pos(info->cursor.cur_pos, info->cursor.command_start_pos);
	dup_pos(info->cursor.command_end_pos, info->cursor.cur_pos);
	command->len = 0;
	display_command(command, info);
}
