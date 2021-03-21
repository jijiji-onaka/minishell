/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 00:06:42 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/20 01:27:22 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

static char	*decide_error_message(char *command, t_minishell *info
			, bool path_flag, char *sla_flag)
{
	struct stat st;
	int			fd;

	if (path_flag)
	{
		if (lstat(command, &st) == -1 && errno != ENOENT)
			all_free_exit(info, ERR_LSTAT, __LINE__, __FILE__);
		g_signal.exit_status = (errno == ENOENT ? 127 : 126);
		errno = (S_ISDIR(st.st_mode) ? EISDIR : errno);
		return (strerror(errno));
	}
	else if (sla_flag)
	{
		fd = open(command, O_WRONLY);
		g_signal.exit_status = (errno == ENOENT ? 127 : 126);
		if (fd != -1 && close(fd) == -1)
			all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
		return (strerror(errno));
	}
	return (NULL);
}

static void	not_builtin(char *command, t_minishell *info
			, bool path_flag)
{
	char	*errno_message;
	char	*sla;

	if ((sla = ft_strchr(command, '/')) && ENOEXEC == errno)
		exit(0);
	if (write(STDERR_FILENO, "minishell: ", 11) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (write(STDERR_FILENO, command, ft_strlen(command)) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (write(STDERR_FILENO, ": ", 2) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (!(errno_message = decide_error_message(command, info, path_flag, sla)))
	{
		if (write(STDERR_FILENO, "command not found\n", 18) < 0)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
		g_signal.exit_status = CMD_NOT_FOUND;
	}
	else if (ft_putendl_fd(errno_message, STDERR_FILENO) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
}

static bool	check_executable_file_in_bin_dir(char *path, char **command,
				t_minishell *info)
{
	t_stat	stat_buf;
	char	*bin_path;

	if (!(bin_path = ft_str3join(path, "/", command[0])))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	if (lstat(bin_path, &stat_buf) == 0)
	{
		ptr_free((void **)&(command[0]));
		command[0] = bin_path;
		return (true);
	}
	ptr_free((void **)&bin_path);
	return (false);
}

static int	check_bash_standard_commands(t_minishell *info, char **command
		, bool *path_flag)
{
	char		*env_path;
	char		**bin_paths;
	int			i;

	if ((*command) == NULL || (*command)[0] == '\0')
		return (true);
	if (((*command)[0] == '.' && (*command)[1] == '\0'))
	{
		write(2, "minishell: .: filename argument required\n\
.: usage: . filename [arguments]\n", 74);
		return (74);
	}
	if (ft_strchr((*command), '/'))
		return (true);
	if ((*command)[0] == '.' && (*command)[1] == '.' && (*command)[2] == '\0')
		return (true);
	if (!(env_path = search_env("PATH", 4, info->env)))
		return ((*path_flag = true));
	if (!(bin_paths = ft_split(env_path, ':')))
		return (-1);
	i = -1;
	while (bin_paths[++i])
		if (check_executable_file_in_bin_dir(bin_paths[i], command, info))
			break ;
	return (!(ptr_2d_free((void ***)&bin_paths, i)));
}

void		exec_bin(t_minishell *info, t_cmdlst *cmd)
{
	int			ret;
	bool		path_flag;
	char		**args;
	extern char	**environ;

	args = cmd->arg;
	if ((g_signal.fork_pid = fork()) == -1)
		all_free_exit(info, ERR_FORK, __LINE__, __FILE__);
	path_flag = false;
	g_signal.exit_status = 0;
	if (g_signal.fork_pid == 0)
	{
		if ((ret = check_bash_standard_commands(info, args, &path_flag)) < 0)
			exit(!ft_perror("write or malloc"));
		if (ret == 74)
			exit(2);
		if ((ret = execve(args[0], args, environ)) == -1)
			not_builtin(args[0], info, path_flag);
		exit(g_signal.exit_status);
	}
	if ((waitpid(g_signal.fork_pid, &ret, 0)) == -1)
		all_free_exit(info, ERR_WAIT_PID, __LINE__, __FILE__);
	if (g_signal.exit_status != 130 && g_signal.exit_status != 131)
		g_signal.exit_status = WEXITSTATUS(ret);
}
