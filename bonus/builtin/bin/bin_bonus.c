/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 00:06:42 by tjinichi          #+#    #+#             */
/*   Updated: 2021/05/22 13:44:58 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bonus_includes/minishell_bonus.h"

void	not_set_path(char **args, char **environ, char *path, t_minishell *info)
{
	execve(args[0], args, environ);
	not_builtin(args[0], info, path);
	exit(g_global.exit_status);
}

static void	clean_up(char ***environ, int i, char ***split, t_minishell *info)
{
	int	status;

	(void)i;
	if ((waitpid(g_global.fork_pid, &status, 0)) == -1)
		all_free_exit(info, ERR_WAIT_PID, __LINE__, __FILE__);
	ptr_2d_free((void ***)environ, -1);
	if (*split)
		ptr_2d_free((void ***)split, -1);
	if (g_global.exit_status != 130 && g_global.exit_status != 131)
		g_global.exit_status = WEXITSTATUS(status);
	if (info->minishell_op_c == false)
		tcsetattr(STDIN, TCSAFLUSH, &(info->terminal[REPLICA]));
}

void	exec_bin(t_minishell *info, t_cmdlst *cmd)
{
	int			i[2];
	char		**environ;
	char		*path;
	char		**split;

	setting_1(&environ, &path, &split, info);
	if (split)
		i[0] = setting_2(path, &(cmd->arg[0]), &split, info);
	g_global.fork_pid = fork();
	if (g_global.fork_pid == -1)
		all_free_exit(info, ERR_FORK, __LINE__, __FILE__);
	if (g_global.fork_pid == 0)
	{
		if (split == NULL)
			not_set_path(cmd->arg, environ, path, info);
		i[1] = -1;
		while (split[++i[1]])
			execve(split[i[1]], cmd->arg, environ);
		if (split[i[1]] == NULL)
			execve(cmd->arg[0], cmd->arg, environ);
		not_builtin(cmd->arg[0], info, path);
		exit(g_global.exit_status);
	}
	free(path);
	clean_up(&environ, i[0], &split, info);
}
