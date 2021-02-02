/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 20:52:49 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/27 19:13:41 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipe_redirect.h"

// void	free_alloc_ptr_in_cmd_lst(t_cmdlst **cmd_lst)
// {
// 	if ((*cmd_lst)->arg != NULL)
// 		ptr_2d_free((void ***)&((*cmd_lst)->arg), ARG_MAX);
// 	ptr_free((void **)cmd_lst);
// }


/*
** パイプをうまく機能させようと思うと、
** 必要のないファイルディスクリプタは片っ端から閉じておく必要があります。
** 無駄に開いている読み出し口や書き込み口があると、入力が終わってもEOFが返されません。
** するとパイプで繋がれたプログラムが終了しないので、いつまでも待ち続ける羽目になります。
** 必要なものだけ開いた状態にするのが鉄則です。
** (引用) https://www.haya-programming.com/entry/2018/11/08/185349
*/

void	apply_last_pipe(t_cmdlst **cmd_lst, int pipefd[2],
							t_minishell_info *info)
{
	int	fork_pid;
	int	status;

	if ((fork_pid = fork()) == -1)
		all_free_exit(info, ERR_FORK, __LINE__, __FILE__);
	else if (fork_pid == 0)
	{
		// puts("dddddd");
		connect_std_in_out_and_pipe(pipefd, STDIN_FILENO, info);
		execute_each_command(info, *cmd_lst);
		exit(0);
	}
	close_pipe_fd(pipefd, info);
	if (waitpid(fork_pid, &status, 0) == -1)
		all_free_exit(info, ERR_WAIT_PID, __LINE__, __FILE__);
	if (WIFEXITED(status))
		return ;
	else //シグナルの番号を返すべきか
		all_free_exit(info, ERR_FAIL_CHILD, __LINE__, __FILE__);
}

void	apply_middle_pipe(t_cmdlst **cmd_lst, int old_pipefd[2],
						int new_pipefd[2], t_minishell_info *info)
{
	int	fork_pid;
	int	status;

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
	if (waitpid(fork_pid, &status, 0) == -1)
		all_free_exit(info, ERR_WAIT_PID, __LINE__, __FILE__);
	if (WIFEXITED(status))
		return ;
	else //シグナルの番号を返すべきか
		all_free_exit(info, ERR_FAIL_CHILD, __LINE__, __FILE__);
}

void	apply_first_pipe(t_cmdlst **cmd_lst, int pipefd[2],
						t_minishell_info *info)
{
	int	fork_pid;
	int	status;

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
	if (waitpid(fork_pid, &status, 0) == -1)
		all_free_exit(info, ERR_WAIT_PID, __LINE__, __FILE__);
	if (WIFEXITED(status))
		return ;
	else //シグナルの番号を返すべきか
		all_free_exit(info, ERR_FAIL_CHILD, __LINE__, __FILE__);
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
	apply_first_pipe(cmd_lst, pipefd[i], info);
	*cmd_lst = skip_lst_and_free(cmd_lst, 2);
	i++;
		// puts("?????????");
	while (*cmd_lst && ((*cmd_lst)->type == PIPE || ((*cmd_lst)->next &&
				(*cmd_lst)->next->type == PIPE)))
	{
		apply_middle_pipe(cmd_lst, pipefd[i - 1], pipefd[i], info);
		*cmd_lst = skip_lst_and_free(cmd_lst, 2);
		i++;
		// if ((*cmd_lst)->type != PIPE)
		// {
		// 	apply_middle_pipe(cmd_lst, pipefd[i - 1], pipefd[i], info);
		// 	i++;
		// }
		// next = (*cmd_lst)->next;
		// free_alloc_ptr_in_cmd_lst(cmd_lst);
		// *cmd_lst = next;
	}
	apply_last_pipe(cmd_lst, pipefd[i - 1], info);
	next = (*cmd_lst)->next;
	free_alloc_ptr_in_cmd_lst(cmd_lst);
	return (next);
}
