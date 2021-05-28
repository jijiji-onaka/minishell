/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 15:05:11 by tjinichi          #+#    #+#             */
/*   Updated: 2021/05/25 21:20:08 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bonus_includes/minishell_bonus.h"

static void	preparation(int *backup, t_string *command,
					char *stopper, t_minishell *info)
{
	if (write(STDOUT, "(", 1) < 1)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (write(STDOUT, stopper, ft_strlen(stopper)) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (write(STDOUT, ")", 1) < 1)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (write(STDOUT, "> ", 2) < 2)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	*backup = dup(STDIN);
	if (*backup == -1)
		all_free_exit(info, ERR_DUP, __LINE__, __FILE__);
	command->str = ft_strdup("");
	if (command->str == NULL)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	command->len = 0;
	g_global.reading = true;
	get_cursor_position(info->cursor.command_start_pos, info);
	dup_pos(info->cursor.cur_pos, info->cursor.command_start_pos);
	dup_pos(info->cursor.command_end_pos, info->cursor.command_start_pos);
}

static bool	is_matched(t_string *command, char *stopper,
				int fd, bool expand_flag)
{
	if (ft_strcmp(command->str, stopper) == 0)
	{
		ptr_free((void **)&(command->str));
		return (true);
	}
	if (expand_flag)
		change_env_for_here_doc(&(command->str), &(g_global.info));
	if (ft_putendl_fd(command->str, fd) == false)
		all_free_exit(&(g_global.info), ERR_WRITE, __LINE__, __FILE__);
	command->str = re_strdup(&(command->str), "\0");
	if (command->str == NULL)
		all_free_exit(&(g_global.info), ERR_MALLOC, __LINE__, __FILE__);
	command->len = 0;
	if (write(STDOUT, "(", 1) < 1)
		all_free_exit(&(g_global.info), ERR_WRITE, __LINE__, __FILE__);
	if (write(STDOUT, stopper, ft_strlen(stopper)) < 0)
		all_free_exit(&(g_global.info), ERR_WRITE, __LINE__, __FILE__);
	if (write(STDOUT, ")", 1) < 1)
		all_free_exit(&(g_global.info), ERR_WRITE, __LINE__, __FILE__);
	if (write(STDOUT, "> ", 2) < 2)
		all_free_exit(&(g_global.info), ERR_WRITE, __LINE__, __FILE__);
	return (false);
}

static void	clean_up(int *backup, t_string *command, t_minishell *info)
{
	ptr_free((void **)&(command->str));
	if (!g_global.reading)
	{
		if ((dup2(*backup, STDIN)) == -1)
		{
			all_free_exit(info, ERR_DUP2, __LINE__, __FILE__);
		}
	}
	if (ft_close(backup) == false)
	{
		all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	}
}

bool	do_here_document(t_minishell *info, int fd, char *stopper,
									bool expand_flag)
{
	char		buf[READ_SIZE + 1];
	t_string	command;
	ssize_t		rc;
	int			backup;

	preparation(&backup, &command, stopper, info);
	g_global.sig_sign = 0;
	while (g_global.reading)
	{
		rc = safe_read(buf, &(command.str), info);
		if (rc == -1)
			break ;
		if (buf[0] == 4 && command.str[0] == '\0')
			break ;
		check_key(buf, &command, info);
		if (ft_strchr(buf, '\n') != NULL)
			if (is_matched(&command, stopper, fd, expand_flag)
				== true)
				break ;
	}
	clean_up(&backup, &command, info);
	g_global.sig_sign = 1;
	if (!g_global.reading)
		return (reset_prompt(NULL, NULL));
	return (true);
}
