/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting_for_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 01:01:05 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/29 21:31:12 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	preparation(int *backup, t_string *command,
					char buf[4], t_minishell *info)
{
	if ((*backup = dup(STDIN_FILENO)) == -1)
		all_free_exit(info, ERR_DUP, __LINE__, __FILE__);
	if (!(command->str = ft_strdup("")))
	{
		if (ft_close(backup) == false)
			all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	}
	command->len = 0;
	buf[0] = '\0';
	g_global.reading = true;
	info->history_flag = false;
	info->command_history = info->command_history_begin;
	info->key.save_command_len = 0;
}

static void	clean_up(int *backup, char **command, t_minishell *info)
{
	if (!g_global.reading)
		if ((dup2(*backup, STDIN_FILENO)) == -1)
		{
			ptr_free((void**)command);
			all_free_exit(info, ERR_DUP2, __LINE__, __FILE__);
		}
	if (ft_close(backup) == false)
	{
		ptr_free((void**)command);
		all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	}
	if (info->ptr_for_free)
		ptr_free((void**)&(info->ptr_for_free));
	info->command_history = info->command_history_begin;
}

t_history	*make_struct_history(int fd, char *line, t_history *prev,
						t_minishell *info)
{
	t_history	*new;

	new = malloc(sizeof(t_history));
	if (new == NULL)
	{
		close(fd);
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	}
	new->command = line;
	new->next = NULL;
	new->prev = prev;
	return (new);
}
void		update_command_history(char *command, t_minishell *info)
{
	t_history	*begin;

	if (command == NULL)
		return ;
	if (info->command_history == NULL)
	{
		info->command_history = make_struct_history(0, command, NULL, info);
		info->command_history_begin = info->command_history;
	}
	else
	{
		info->command_history->next = make_struct_history(0, command, info->command_history, info);
		info->command_history_begin = info->command_history->next;
	}
}

char		*waiting_for_input(t_minishell *info)
{
	t_string	command;
	char		buf[READ_SIZE + 1];
	ssize_t		rc;
	int			backup;

	// printf("[%d : %d]\n", tgetnum("co"), tgetnum("li"));
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
	if (!g_global.reading)
		return (reset_prompt(&(command.str), NULL));
	update_command_history(command.str, info);
	return (command.str);
}
