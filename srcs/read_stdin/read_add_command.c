/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_add_command.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 16:00:32 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/09 13:11:44 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	preparation(int *backup, t_string *add_command, t_minishell *info)
{
	add_command->str = ft_strdup("");
	if (add_command->str == NULL)
		all_free_exit(info, ERR_MALLOC, LINE, FILE);
	*backup = dup(STDIN);
	if (*backup == -1)
	{
		ptr_free((void **)(add_command->str));
		all_free_exit(info, ERR_DUP, LINE, FILE);
	}
	g_global.reading = true;
}

static void	clean_up(int *backup, char **command, t_minishell *info)
{
	ptr_free((void **)command);
	if (!g_global.reading)
		if ((dup2(*backup, STDIN)) == -1)
			all_free_exit(info, ERR_DUP2, __LINE__, __FILE__);
	if (ft_close(backup) == false)
		all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
}

static void	command_joint(t_string *command, t_string *add_command,
							int (*is_valid)(char *), t_minishell *info)
{
	if (is_valid == is_valid_command_pipe)
	{
		command->len = command->len + ft_strlen(add_command->str) + 1;
		command->str = re_str3join(&(command->str), (command->str),
				" ", add_command->str);
		if (command->str == NULL)
			all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	}
	else
	{
		command->str[command->len - 1] = '\0';
		command->len = command->len + ft_strlen(add_command->str) - 1;
		command->str = re_strjoin(&(command->str), (command->str),
				add_command->str);
		if (command->str == NULL)
			all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	}
}

static bool	is_valid_command(t_string *command, t_string *add_command,
						int (*is_valid)(char *), t_minishell *info)
{
	if (add_command->str == NULL)
		add_command->str = ft_strdup("");
	if (add_command->str == NULL)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	command_joint(command, add_command, is_valid, info);
	if (is_valid(add_command->str) == true)
		return (true);
	display_what_is_waiting_for(42, NULL, &(command->str), info);
	add_command->str = re_strdup(&(add_command->str), "");
	if (add_command->str == NULL)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	return (false);
}

char	*read_add_command(t_string *command,
				int (*is_valid)(char *), t_minishell *info)
{
	char		buf[READ_SIZE + 1];
	t_string	add_command;
	ssize_t		rc;
	int			backup;

	display_what_is_waiting_for(42, NULL, &(command->str), info);
	preparation(&backup, &add_command, info);
	while (g_global.reading)
	{
		rc = safe_read(buf, &(command->str), info);
		if (rc == -1)
			break ;
		check_key_multiple_line('|', buf, &add_command, info);
		if (ft_strchr(buf, '\n') != NULL)
			if (is_valid_command(command, &add_command, is_valid, info) == true)
				break ;
	}
	clean_up(&backup, &(add_command.str), info);
	if (!g_global.reading)
		return (reset_prompt(&(command->str), NULL));
	return (command->str);
}
