/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_builtin_command_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 14:23:17 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/04 03:01:28 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell_bonus.h"

static char	*decide_error_message_2(char *command, t_minishell *info
			, bool path_flag, bool sla_flag)
{
	int			fd;

	(void)sla_flag;
	if (path_flag)
	{
		fd = open(command, O_WRONLY);
		g_global.exit_status = (errno == ENOENT ? 127 : 126);
		if (fd != -1 && close(fd) == -1)
			all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
		return (strerror(errno));
	}
	g_global.exit_status = CMD_NOT_FOUND;
	return (NULL);
}

static char	*decide_error_message(char *command, t_minishell *info
			, bool path_flag, bool sla_flag)
{
	struct stat	st;
	int			fd;

	if (sla_flag)
	{
		lstat(command, &st);
		if (S_ISREG(st.st_mode) && ((S_IXUSR | S_IXGRP | S_IXOTH) & st.st_mode))
		{
			if (errno == EACCES && !(S_IRUSR & st.st_mode))
			{
				g_global.exit_status = 126;
				return (strerror(errno));
			}
			exit(0);
		}
		fd = open(command, O_WRONLY);
		g_global.exit_status = (errno == ENOENT ? 127 : 126);
		if (fd != -1 && close(fd) == -1)
			all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
		if (errno == EISDIR)
			return ("is a directory");
		return (strerror(errno));
	}
	return (decide_error_message_2(command, info, path_flag, sla_flag));
}

void		not_builtin(char *command, t_minishell *info
			, bool path_flag)
{
	char	*errno_message;

	if (ENOEXEC == errno)
		errno = EACCES;
	if (!(errno_message = decide_error_message(command, info, path_flag,
		ft_strchr(command, '/'))))
		errno_message = "command not found";
	if (write(STDERR, "minishell: ", 11) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (write(STDERR, command, ft_strlen(command)) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (write(STDERR, ": ", 2) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	else if (ft_putendl_fd(errno_message, STDERR) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
}
