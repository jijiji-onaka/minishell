/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipe_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 01:31:14 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/09 14:53:47 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	close_pipe_fd(int pipefd[2], t_minishell *info)
{
	if (close(pipefd[STDIN_FILENO]) == -1)
		all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	if (close(pipefd[STDOUT_FILENO]) == -1)
		all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
}
