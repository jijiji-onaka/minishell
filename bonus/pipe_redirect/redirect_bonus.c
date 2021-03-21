/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 19:45:17 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/20 13:43:04 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

static t_cmdlst	*preparation(int (*fd)[2], t_cmdlst **cmd_lst)
{
	t_cmdlst	*begin;

	begin = *cmd_lst;
	*cmd_lst = (*cmd_lst)->next;
	while (*cmd_lst && is_redir((*cmd_lst)->type) && (*cmd_lst)->next)
	{
		fd[(*cmd_lst)->fd][0] = -1;
		fd[(*cmd_lst)->fd][1] = -1;
		*cmd_lst = (*cmd_lst)->next->next;
	}
	*cmd_lst = begin;
	begin = *cmd_lst;
	*cmd_lst = (*cmd_lst)->next;
	return (begin);
}

static void		redirect_put(int (*fd)[2], t_cmdlst **lst, int num,
				t_minishell *info)
{
	int			backup[num + 1];
	int			i;
	t_cmdlst	*begin;

	i = 0;
	while (i < num + 1)
		backup[i++] = -1;
	begin = *lst;
	prepare_redirect_put(fd, backup, (*lst)->next, info);
	get_arg_behind_redir((*lst), info);
	(*lst)->fd = (*lst)->next->fd;
	if (*lst && (*lst)->next && (*lst)->next->next &&
		(*lst)->next->next->next && (*lst)->next->next->next->type == PIPE
		&& !((*lst)->checker_pipe))
		;
	else
	{
		(*lst)->checker_redir = true;
		execute_command(info, (lst));
	}
	cleanup_redirect_put(fd, backup, begin->next, info);
}

static t_cmdlst	*my_redirect_main(t_minishell *info,
					t_cmdlst **cmd_lst, int redir_num, int total)
{
	t_cmdlst	*begin;
	int			rc;
	int			fd[redir_num + 1][2];

	begin = preparation(fd, cmd_lst);
	rc = open_files_and_stock_fd(fd, cmd_lst, info);
	if (rc == false || rc == -1)
	{
		skip_cmdlst(cmd_lst, total * 2, false);
		if (rc == false)
			return (*cmd_lst);
		all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	}
	redirect_put(fd, &begin, redir_num, info);
	*cmd_lst = begin;
	(*cmd_lst)->checker_redir = true;
	skip_cmdlst(cmd_lst, total * 2, false);
	return (*cmd_lst);
}

t_cmdlst		*my_redirect(t_minishell *info,
					t_cmdlst **cmd_lst)
{
	t_cmdlst	*begin;
	int			max_fd;
	int			redir_num;
	int			total_num;

	begin = *cmd_lst;
	*cmd_lst = (*cmd_lst)->next;
	max_fd = -1;
	redir_num = 0;
	total_num = 0;
	while (*cmd_lst && (is_redir((*cmd_lst)->type) && (*cmd_lst)->next))
	{
		if (max_fd < (*cmd_lst)->fd)
			max_fd = (*cmd_lst)->fd;
		if (is_redir((*cmd_lst)->type))
			redir_num++;
		total_num++;
		*cmd_lst = (*cmd_lst)->next->next;
	}
	*cmd_lst = begin;
	if (max_fd < redir_num)
		max_fd = redir_num;
	return (my_redirect_main(info, cmd_lst, max_fd, total_num));
}
