/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 19:45:17 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 17:47:45 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_cmdlst	*prepare_in_advance(int fd[3], t_cmdlst **cmd_lst)
{
	t_cmdlst	*begin;

	fd[0] = -1;
	fd[1] = -1;
	fd[2] = -1;
	begin = *cmd_lst;
	*cmd_lst = (*cmd_lst)->next;
	return (begin);
}

t_cmdlst		*redirect_sep(t_minishell_info *info, t_cmdlst **cmd_lst)
{
	t_cmdlst	*begin;
	int			rc;
	int			fd[3];

	begin = prepare_in_advance(fd, cmd_lst);
	rc = open_files_and_stock_fd(fd, begin->type, cmd_lst, info);
	if (rc == false || rc == -1)
	{
		free_alloc_ptr_in_cmd_lst(&begin);
		if (rc == false)
			return (skip_lst_and_free(cmd_lst, ARG_MAX));
		all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	}
	if (fd[0] != -1 && fd[1] != -1)
		mix_input_and_output(fd, begin, info);
	else if (fd[2] != -1 && fd[1] != -1)
		mix_input_and_stderr_output(fd, begin, info);
	else if (fd[1] != -1)
		read_from_file(fd[1], begin, info);
	else if (fd[2] != -1)
		write_to_file(fd[2], STDERR_FILENO, begin, info);
	else if (fd[0] != -1)
		write_to_file(fd[0], STDOUT_FILENO, begin, info);
	free_alloc_ptr_in_cmd_lst(&begin);
	return (*cmd_lst);
}
