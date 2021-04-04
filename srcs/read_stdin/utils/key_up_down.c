/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_up_down.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:50:46 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/04 10:17:48 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	delete_displayed_command1(t_err err, t_string *command,
							t_minishell *info)
{
	int		i;
	int		len;

	putstr_fd(info->key.save, STDIN, err, info);
	move_specified_position(info->cursor.command_end_pos[Y],
		info->cursor.command_end_pos[X], err, info);
	dup_pos(info->cursor.cur_pos, info->cursor.command_end_pos);
	len = get_command_len_from_pos(info->cursor.command_end_pos,
		info->cursor.command_start_pos, info->window.ws.ws_col);
	i = -1;
	while (++i < len)
		delete_displayed_char(NULL, command, info);
	putstr_fd(info->key.restore, STDIN, err, info);
}

void	trace_history_up(char *buf, t_string *command, t_minishell *info)
{
	char	*history_command;

	if (info->command_history == NULL)
		return ;
	delete_displayed_command1(where_err(LINE, FILE), command, info);
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
	command->str = history_command;
	dup_pos(info->cursor.cur_pos, info->cursor.command_start_pos);
	dup_pos(info->cursor.command_end_pos, info->cursor.cur_pos);
	display_command(command, info);
}

void	trace_history_down(char *buf, t_string *command, t_minishell *info)
{
	char	*history_command;

	if (info->command_history == NULL
		|| (info->history_flag == false && info->command_history->next == NULL))
		return ;
	delete_displayed_command1(where_err(LINE, FILE), command, info);
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
	command->str = history_command;
	dup_pos(info->cursor.cur_pos, info->cursor.command_start_pos);
	dup_pos(info->cursor.command_end_pos, info->cursor.cur_pos);
	display_command(command, info);
}
