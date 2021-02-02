/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 20:52:49 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 17:48:09 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** パイプをうまく機能させようと思うと、
** 必要のないファイルディスクリプタは片っ端から閉じておく必要があります。
** 無駄に開いている読み出し口や書き込み口があると、入力が終わってもEOFが返されません。
** するとパイプで繋がれたプログラムが終了しないので、いつまでも待ち続ける羽目になります。
** 必要なものだけ開いた状態にするのが鉄則です。
** (引用) https://www.haya-programming.com/entry/2018/11/08/185349
*/

static void	apply_last_pipe(t_cmdlst **cmd_lst, int pipefd[2],
							t_minishell_info *info)
{
	int	fork_pid;

	if ((fork_pid = fork()) == -1)
		all_free_exit(info, ERR_FORK, __LINE__, __FILE__);
	else if (fork_pid == 0)
	{
		connect_std_in_out_and_pipe(pipefd, STDIN_FILENO, info);
		execute_each_command(info, *cmd_lst);
		exit(0);
	}
	close_pipe_fd(pipefd, info);
}

static void	apply_middle_pipe(t_cmdlst **cmd_lst, int old_pipefd[2],
						int new_pipefd[2], t_minishell_info *info)
{
	int	fork_pid;

	if ((pipe(new_pipefd)) == -1)
		all_free_exit(info, ERR_PIPE, __LINE__, __FILE__);
	if ((fork_pid = fork()) == -1)
		all_free_exit(info, ERR_FORK, __LINE__, __FILE__);
	else if (fork_pid == 0)
	{
		connect_std_in_out_and_pipe(old_pipefd, STDIN_FILENO, info);
		connect_std_in_out_and_pipe(new_pipefd, STDOUT_FILENO, info);
		execute_each_command(info, *cmd_lst);
		exit(0);
	}
	close_pipe_fd(old_pipefd, info);
}

static void	apply_first_pipe(t_cmdlst **cmd_lst, int pipefd[2],
						t_minishell_info *info)
{
	int	fork_pid;

	if ((pipe(pipefd)) == -1)
		all_free_exit(info, ERR_FORK, __LINE__, __FILE__);
	if ((fork_pid = fork()) == -1)
		all_free_exit(info, ERR_FORK, __LINE__, __FILE__);
	else if (fork_pid == 0)
	{
		connect_std_in_out_and_pipe(pipefd, STDOUT_FILENO, info);
		execute_each_command(info, *cmd_lst);
		exit(0);
	}
}

/*
** pipefd[1]に入れたデータはpipefd[0]から取り出せる
** dup2(pipefd[1], 1)とすると標準出力先がpipefd[1]、つまりパイプの入り口とつながります
*/

t_cmdlst	*pipe_sep(t_minishell_info *info, t_cmdlst **cmd_lst)
{
	int			pipefd[info->cmd_lst_num / 2][2];
	t_cmdlst	*next;
	int			i;

	i = 0;
	apply_first_pipe(cmd_lst, pipefd[0], info);
	*cmd_lst = skip_lst_and_free(cmd_lst, 2);
	i++;
	while (*cmd_lst && ((*cmd_lst)->type == PIPE || ((*cmd_lst)->next &&
				(*cmd_lst)->next->type == PIPE)))
	{
		apply_middle_pipe(cmd_lst, pipefd[i - 1], pipefd[i], info);
		*cmd_lst = skip_lst_and_free(cmd_lst, 2);
		i++;
	}
	apply_last_pipe(cmd_lst, pipefd[i - 1], info);
	while (wait(NULL) > 0)
		;
	next = (*cmd_lst)->next;
	return (next);
}
