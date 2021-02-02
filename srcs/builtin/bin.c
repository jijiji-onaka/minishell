/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 00:06:42 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 17:01:38 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	put_cmd_not_found(char *command, t_minishell_info *info)
{
	if (write(STDERR_FILENO, "minishell: ", 11) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (write(STDERR_FILENO, command, ft_strlen(command)) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (write(STDERR_FILENO, ": command not found\n", 20) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
}

static bool	check_executable_file_in_bin_dir(char *path, char **command,
				t_minishell_info *info)
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

static bool	check_bash_standard_commands(t_minishell_info *info, char **command)
{
	char		*env_path;
	char		**bin_paths;
	int			i;

	env_path = search_env("PATH", 4, info->env);
	if (!(bin_paths = ft_split(env_path, ':')))
	{
		ptr_2d_free((void ***)command, ARG_MAX);
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	}
	i = 0;
	while (bin_paths[i])
	{
		if (check_executable_file_in_bin_dir(bin_paths[i], command, info))
			break ;
		i++;
	}
	ptr_2d_free((void ***)&bin_paths, i);
	return (true);
}

void		exec_bin(t_minishell_info *info, char **args)
{
	int			return_val;
	pid_t		wait_pid;
	int			status;
	extern char	**environ;

	return_val = 0;
	if ((g_signal.fork_pid = fork()) == -1)
		all_free_exit(info, ERR_FORK, __LINE__, __FILE__);
	else if (g_signal.fork_pid == 0)
	{
		check_bash_standard_commands(info, args);
		return_val = execve(args[0], args, environ);
		if (errno == ENOENT || errno == EACCES || errno == ENOEXEC)
			put_cmd_not_found(args[0], info);
		else if (return_val == -1)
			all_free_exit(info, ERR_EXECVE, __LINE__, __FILE__);
		exit(CMD_NOT_FOUND);
	}
	if ((wait_pid = waitpid(g_signal.fork_pid, &status, 0)) == -1)
		all_free_exit(info, ERR_WAIT_PID, __LINE__, __FILE__);
	if (g_signal.exit_status != 130)
		g_signal.exit_status = WEXITSTATUS(status);
	if (WIFEXITED(status) || WEXITSTATUS(status) == 0)
		return ;
	all_free_exit(info, ERR_FAIL_CHILD, __LINE__, __FILE__);
}
