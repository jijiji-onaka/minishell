/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 20:52:49 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/04 03:01:19 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** https://www.haya-programming.com/entry/2018/11/08/185349
*/

static void	apply_last_pipe(t_cmdlst **cmd_lst, int pipefd[2],
							t_minishell *info)
{
	(*cmd_lst)->checker_pipe = true;
	if ((g_global.fork_pid_for_pipe = fork()) == -1)
		all_free_exit(info, ERR_FORK, __LINE__, __FILE__);
	else if (g_global.fork_pid_for_pipe == 0)
	{
		connect_std_in_out_and_pipe(pipefd, STDIN, info);
		if (!((*cmd_lst)->checker_redir) && (*cmd_lst && (*cmd_lst)->next
		&& is_redir((*cmd_lst)->next->type)))
			*cmd_lst = my_redirect(info, cmd_lst);
		else if (!((*cmd_lst)->checker_redir) && (*cmd_lst && (*cmd_lst) &&
		is_redir((*cmd_lst)->type)))
			*cmd_lst = redir_first(info, cmd_lst);
		else
			execute_command(info, *cmd_lst);
		exit(g_global.exit_status);
	}
	close_pipe_fd(pipefd, info);
}

static void	apply_middle_pipe(t_cmdlst **cmd_lst, int old_pipefd[2],
						int new_pipefd[2], t_minishell *info)
{
	(*cmd_lst)->checker_pipe = true;
	if ((pipe(new_pipefd)) == -1)
		all_free_exit(info, ERR_PIPE, __LINE__, __FILE__);
	if ((g_global.fork_pid_for_pipe = fork()) == -1)
		all_free_exit(info, ERR_FORK, __LINE__, __FILE__);
	else if (g_global.fork_pid_for_pipe == 0)
	{
		g_global.exit_status = 0;
		connect_std_in_out_and_pipe(old_pipefd, STDIN, info);
		connect_std_in_out_and_pipe(new_pipefd, STDOUT, info);
		if (!((*cmd_lst)->checker_redir) && (*cmd_lst && (*cmd_lst)->next
		&& is_redir((*cmd_lst)->next->type)))
			*cmd_lst = my_redirect(info, cmd_lst);
		else if (!((*cmd_lst)->checker_redir) && (*cmd_lst && (*cmd_lst) &&
		is_redir((*cmd_lst)->type)))
			*cmd_lst = redir_first(info, cmd_lst);
		else
			execute_command(info, *cmd_lst);
		exit(g_global.exit_status);
	}
	close_pipe_fd(old_pipefd, info);
}

static void	apply_first_pipe(t_cmdlst **cmd_lst, int pipefd[2],
						t_minishell *info, int fd)
{
	(void)fd;
	(*cmd_lst)->checker_pipe = true;
	g_global.fork_pid_for_pipe = -1;
	if ((pipe(pipefd)) == -1)
		all_free_exit(info, ERR_FORK, __LINE__, __FILE__);
	if ((g_global.fork_pid_for_pipe = fork()) == -1)
		all_free_exit(info, ERR_FORK, __LINE__, __FILE__);
	else if (g_global.fork_pid_for_pipe == 0)
	{
		connect_std_in_out_and_pipe(pipefd, STDOUT, info);
		if (!((*cmd_lst)->checker_redir) && (*cmd_lst && (*cmd_lst)->next
		&& is_redir((*cmd_lst)->next->type)))
			*cmd_lst = my_redirect(info, cmd_lst);
		else if (!((*cmd_lst)->checker_redir) && (*cmd_lst && (*cmd_lst) &&
		is_redir((*cmd_lst)->type)))
			*cmd_lst = redir_first(info, cmd_lst);
		else
			execute_command(info, *cmd_lst);
		exit(g_global.exit_status);
	}
}

t_cmdlst	*my_pipe(t_minishell *info, t_cmdlst **cmd_lst, int fd)
{
	int			pipefd[info->cmd_lst_num / 2][2];
	int			i;
	int			status;

	apply_first_pipe(cmd_lst, pipefd[0], info, fd);
	skip_command(cmd_lst);
	i = 1;
	while (is_now_middle_pipe(*cmd_lst))
	{
		*cmd_lst = (*cmd_lst)->next;
		apply_middle_pipe(cmd_lst, pipefd[i - 1], pipefd[i], info);
		skip_command(cmd_lst);
		i++;
	}
	*cmd_lst = get_next_command(*cmd_lst);
	apply_last_pipe(cmd_lst, pipefd[i - 1], info);
	if ((waitpid(g_global.fork_pid_for_pipe, &status, 0)) == -1)
		all_free_exit(info, ERR_WAIT_PID, __LINE__, __FILE__);
	g_global.exit_status = WEXITSTATUS(status);
	g_global.fork_pid_for_pipe = -1;
	while (wait(NULL) > 0)
		;
	g_global.sig_sign = 1;
	skip_command(cmd_lst);
	return (*cmd_lst);
}
