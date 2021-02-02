/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mix_input_and_stderr_output.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 01:26:09 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 17:33:08 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void		mix_input_and_stderr_output(int fd[3], t_cmdlst *begin,
				t_minishell_info *info)
{
	int	backup_stdin;
	int	backup_stderr;

	if ((backup_stdin = dup(STDIN_FILENO)) == -1)
		all_free_exit(info, ERR_DUP, __LINE__, __FILE__);
	if (dup2(fd[1], STDIN_FILENO) == -1)
		all_free_exit(info, ERR_DUP2, __LINE__, __FILE__);
	if ((backup_stderr = dup(STDERR_FILENO)) == -1)
		all_free_exit(info, ERR_DUP, __LINE__, __FILE__);
	if (dup2(fd[0], STDERR_FILENO) == -1)
		all_free_exit(info, ERR_DUP2, __LINE__, __FILE__);
	execute_each_command(info, begin);
	if (dup2(backup_stderr, STDERR_FILENO) == -1)
		all_free_exit(info, ERR_DUP2, __LINE__, __FILE__);
	if (close(fd[0]) == -1) // これはいらないかもdup2で勝手にクローズされる？
		all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	if (close(backup_stderr) == -1)
		all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	if (dup2(backup_stdin, STDIN_FILENO) == -1)
		all_free_exit(info, ERR_DUP2, __LINE__, __FILE__);
	if (close(fd[1]) == -1) // これはいらないかもdup2で勝手にクローズされる？
		all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	if (close(backup_stdin) == -1)
		all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
}
