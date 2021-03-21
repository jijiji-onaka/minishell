/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_std_in_out_and_pipe.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 01:31:41 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/17 04:37:54 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell_bonus.h"

void	connect_std_in_out_and_pipe(int pipefd[2], int i_o,
				t_minishell *info)
{
	if (dup2(pipefd[i_o], i_o) == -1)
		all_free_exit(info, ERR_DUP2, __LINE__, __FILE__);
	if (close(pipefd[STDIN_FILENO]) == -1)
		all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	if (close(pipefd[STDOUT_FILENO]) == -1)
		all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
}
