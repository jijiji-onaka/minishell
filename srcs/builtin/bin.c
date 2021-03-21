/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 00:06:42 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/21 14:57:40 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*decide_error_message_2(char *command, t_minishell *info
			, bool path_flag, bool sla_flag)
{
	int			fd;

	(void)sla_flag;
	if (path_flag)
	{
		fd = open(command, O_WRONLY);
		g_signal.exit_status = (errno == ENOENT ? 127 : 126);
		if (fd != -1 && close(fd) == -1)
			all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
		return (strerror(errno));
	}
	g_signal.exit_status = CMD_NOT_FOUND;
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
				g_signal.exit_status = 126;
				return (strerror(errno));
			}
			exit(0);
		}
		fd = open(command, O_WRONLY);
		g_signal.exit_status = (errno == ENOENT ? 127 : 126);
		if (fd != -1 && close(fd) == -1)
			all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
		if (errno == EISDIR)
			return ("is a directory");
		return (strerror(errno));
	}
	if (path_flag)
	{
		fd = open(command, O_WRONLY);
		g_signal.exit_status = (errno == ENOENT ? 127 : 126);
		if (fd != -1 && close(fd) == -1)
			all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
		return (strerror(errno));
	}
	return (decide_error_message_2(command, info, path_flag, sla_flag));
}

static void	not_builtin(char *command, t_minishell *info
			, bool path_flag)
{
	char	*errno_message;

	if (ENOEXEC == errno)
		errno = EACCES;
	if (!(errno_message = decide_error_message(command, info, path_flag,
		ft_strchr(command, '/'))))
		errno_message = "command not found";
	if (write(STDERR_FILENO, "minishell: ", 11) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (write(STDERR_FILENO, command, ft_strlen(command)) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (write(STDERR_FILENO, ": ", 2) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	else if (ft_putendl_fd(errno_message, STDERR_FILENO) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
}

void		exec_bin(t_minishell *info, t_cmdlst *cmd)
{
	int			ret;
	bool		path_flag;
	char		**path;

	path = get_path(info->env, info);
	if ((g_signal.fork_pid = fork()) == -1)
		all_free_exit(info, ERR_FORK, __LINE__, __FILE__);
	path_flag = false;
	g_signal.exit_status = 0;
	if (g_signal.fork_pid == 0)
	{
		if ((ret = check_bash_standard_commands(info, cmd->arg, &path_flag)) < 0)
			exit(!ft_perror("write or malloc"));
		if (ret == 74)
			exit(2);
		if ((ret = execve(cmd->arg[0], cmd->arg, path)) == -1)
			not_builtin(cmd->arg[0], info, path_flag);
		exit(g_signal.exit_status);
	}
	ptr_2d_free((void***)&path, 0);
	if ((waitpid(g_signal.fork_pid, &ret, 0)) == -1)
		all_free_exit(info, ERR_WAIT_PID, __LINE__, __FILE__);
	if (g_signal.exit_status != 130 && g_signal.exit_status != 131)
		g_signal.exit_status = WEXITSTATUS(ret);
}
