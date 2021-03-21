/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 00:06:42 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/21 20:20:21 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	setting_1(char ***environ, char **paths,
			char ***split, t_minishell *info)
{
	*environ = get_environ(info->env, info);
	*paths = search_env("PATH", 4, info->env, NULL);
	if (*paths && (*paths)[0] != '\0')
		*split = ft_split(*paths, ':');
	else
		*split = NULL;
	g_signal.exit_status = 0;
}

static int	setting_2(char *paths, char *command,
			char ***split, t_minishell *info)
{
	int		i;
	char	*tmp;

	i = -1;
	while ((*split)[++i])
	{
		tmp = check_executable_file_in_bin_dir((*split)[i], &command, info);
		if (!tmp)
			;
		else
		{
			free((*split)[i]);
			(*split)[i] = tmp;
		}
	}
	(*split)[i] = ft_strdup(command);
	if ((paths[ft_strlen(paths) - 1] == ':' ||
		paths[ft_strlen(paths) - 1] == '/') &&
		no_exe_file_in_bin_dir((*split)[i], info) == true)
		(*split)[i] = re_strjoin(&((*split)[i]), "./", (*split)[i]);
	return (i);
}

void		not_set_path(char **args, char **environ, t_minishell *info)
{
	execve(args[0], args, environ);
	not_builtin(args[0], info, true);
	exit(g_signal.exit_status);
}

static void	clean_up(char ***environ, int i, char ***split, t_minishell *info)
{
	int	status;

	ptr_2d_free((void***)environ, 0);
	if (*split)
	{
		free((*split)[i]);
		(*split)[i] = NULL;
		ptr_2d_free((void***)split, -1);
	}
	if ((waitpid(g_signal.fork_pid, &status, 0)) == -1)
		all_free_exit(info, ERR_WAIT_PID, __LINE__, __FILE__);
	if (g_signal.exit_status != 130 && g_signal.exit_status != 131)
		g_signal.exit_status = WEXITSTATUS(status);
}

void		exec_bin(t_minishell *info, t_cmdlst *cmd)
{
	int			ret;
	int			i[2];
	char		**environ;
	char		*paths;
	char		**split;

	setting_1(&environ, &paths, &split, info);
	if (paths != NULL && paths[0] != '\0')
		i[0] = setting_2(paths, cmd->arg[0], &split, info);
	if ((g_signal.fork_pid = fork()) == -1)
		all_free_exit(info, ERR_FORK, __LINE__, __FILE__);
	if (g_signal.fork_pid == 0)
	{
		if (paths == NULL || paths[0] == '\0')
			not_set_path(cmd->arg, environ, info);
		i[1] = -1;
		while (++i[1] <= i[0])
			execve(split[i[1]], cmd->arg, environ);
		not_builtin(split[i[1] - 1], info, false);
		exit(g_signal.exit_status);
	}
	clean_up(&environ, i[0], &split, info);
}
