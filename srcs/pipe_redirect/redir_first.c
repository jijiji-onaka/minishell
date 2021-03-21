/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_first.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 10:05:01 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/21 14:03:45 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_cmdlst	*preparation(int (*fd)[2], t_cmdlst **cmd_lst)
{
	t_cmdlst	*begin;

	begin = *cmd_lst;
	while (*cmd_lst && is_redir((*cmd_lst)->type) && (*cmd_lst)->next)
	{
		fd[(*cmd_lst)->fd][0] = -1;
		fd[(*cmd_lst)->fd][1] = -1;
		*cmd_lst = (*cmd_lst)->next->next;
	}
	*cmd_lst = begin;
	return (begin);
}

static void		redirect_put(int (*fd)[2], t_cmdlst *lst, int num,
				t_minishell *info)
{
	int			backup[num + 1];
	int			i;
	char		**tmp;

	i = 0;
	while (i < num + 1)
		backup[i++] = -1;
	prepare_redirect_put(fd, backup, lst, info);
	if (lst->next != NULL && lst->next->type != SEMICOLON)
	{
		tmp = lst->arg;
		lst->arg = get_arg_behind_redir_for_first(lst, info);
		lst->type = binary_search(lst->arg[0]);
		lst->checker_redir = true;
		if (lst->next && lst->next->next && lst->next->next->next &&
			lst->next->next->next->type == PIPE && !(lst->checker_pipe))
			;
		else if (lst->arg[0])
			execute_command(info, lst);
		ptr_2d_free((void ***)&(lst->arg), -1);
		lst->arg = tmp;
		lst->type = OUTPUT;
	}
	cleanup_redirect_put(fd, backup, lst, info);
}

static t_cmdlst	*redir_first_main(t_minishell *info,
					t_cmdlst **cmd_lst, int num, int total_num)
{
	t_cmdlst	*begin;
	int			rc;
	int			fd[num + 1][2];

	begin = preparation(fd, cmd_lst);
	rc = open_files_and_stock_fd(fd, cmd_lst, info);
	if (rc == false || rc == -1)
	{
		skip_cmdlst(cmd_lst, total_num * 2, false);
		if (rc == false)
			return (*cmd_lst);
		all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	}
	redirect_put(fd, begin, num, info);
	*cmd_lst = begin;
	(*cmd_lst)->checker_redir = true;
	skip_cmdlst(cmd_lst, total_num * 2, false);
	return (*cmd_lst);
}

t_cmdlst		*redir_first(t_minishell *info, t_cmdlst **cmd_lst)
{
	t_cmdlst	*begin;
	int			max_fd;
	int			redir_num;
	int			total_num;

	begin = *cmd_lst;
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
	return (redir_first_main(info, cmd_lst, max_fd, total_num));
}
