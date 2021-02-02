/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_std_in_out_and_pipe.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 01:31:41 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 17:33:08 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	connect_std_in_out_and_pipe(int pipefd[2], int i_o,
				t_minishell_info *info)
{
	if (dup2(pipefd[i_o], i_o) == -1)
		all_free_exit(info, ERR_DUP2, __LINE__, __FILE__);
	if (close(pipefd[STDIN_FILENO]) == -1)
		all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	if (close(pipefd[STDOUT_FILENO]) == -1)
		all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
}
