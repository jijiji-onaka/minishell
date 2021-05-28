/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 01:01:05 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/09 13:07:44 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../bonus_includes/minishell_bonus.h"

static void	preparation(int *backup, t_string *command,
					char buf[READ_SIZE + 1], t_minishell *info)
{
	t_hist_list	*now_command;

	*backup = dup(STDIN);
	if (*backup == -1)
		all_free_exit(info, ERR_DUP, __LINE__, __FILE__);
	command->str = ft_strdup("");
	if (command->str == NULL)
	{
		if (ft_close(backup) == false)
			all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	}
	command->len = 0;
	buf[0] = '\0';
	g_global.reading = true;
	info->history.list = info->history.begin;
	now_command = make_struct_hist_list(-1, NULL, NULL, info);
	historylist_add_front(&(info->history.list), now_command);
	info->history.list = now_command;
	info->history.begin = now_command;
	info->key.multi_byte_flag = false;
	info->key.multi_byte_flag_2 = false;
	dup_pos(info->cursor.cur_pos, info->cursor.command_start_pos);
	dup_pos(info->cursor.command_end_pos, info->cursor.command_start_pos);
	dup_pos(info->cursor.select_pos, info->cursor.command_start_pos);
}

static void	clean_up(int *backup, char **command, t_minishell *info)
{
	if (!g_global.reading)
	{
		if ((dup2(*backup, STDIN)) == -1)
		{
			ptr_free((void **)command);
			all_free_exit(info, ERR_DUP2, __LINE__, __FILE__);
		}
	}
	if (ft_close(backup) == false)
	{
		ptr_free((void **)command);
		all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	}
	if (info->ptr_for_free)
		ptr_free((void **)&(info->ptr_for_free));
}

static void	update_command_history(t_minishell *info, t_string *command)
{
	if (info->history.list != info->history.begin)
	{
		free(info->history.begin->command);
		info->history.begin->command = ft_strdup(command->str);
		if (info->history.begin->command == NULL)
			all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	}
	else
	{
		free(info->history.list->command);
		info->history.list->command = command->str;
	}
}

static char	*not_command(t_minishell *info, char **command)
{
	t_hist_list	*begin;

	begin = info->history.begin->old_hist;
	free(info->history.begin);
	info->history.begin = begin;
	return (reset_prompt(command, NULL));
}

char	*read_command(t_minishell *info)
{
	t_string	command;
	char		buf[READ_SIZE + 1];
	ssize_t		rc;
	int			backup;

	preparation(&backup, &command, buf, info);
	while (g_global.reading)
	{
		rc = safe_read(buf, &(command.str), info);
		if (rc == -1)
			break ;
		check_key(buf, &command, info);
		if (ft_strchr(buf, '\n') != NULL)
			break ;
	}
	clean_up(&backup, &(command.str), info);
	if (!g_global.reading || command.str == NULL || command.str[0] == '\0'
		|| command.str[0] == '\n')
		return (not_command(info, &(command.str)));
	if (check_format(&command, info) == NULL)
		return (NULL);
	update_command_history(info, &command);
	info->history.list = info->history.begin;
	return (command.str);
}
