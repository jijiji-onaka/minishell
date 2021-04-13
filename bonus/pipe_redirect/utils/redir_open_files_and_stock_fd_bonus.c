/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_open_files_and_stock_fd_bonus.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 01:15:42 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/13 15:41:24 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bonus_includes/minishell_bonus.h"

static int	set_mode(int type)
{
	if (type == OUTPUT)
		return (O_TRUNC);
	else if (type == DB_OUTPUT)
		return (O_APPEND);
	return (0);
}

static bool	when_here_document(int **fd, t_cmdlst **cmd, char **filename,
				t_minishell *info)
{
	char	*stop;
	int		src_i;
	int		dst_i;

	if ((fd[(*cmd)->fd][0] = open("./bonus/tmp", O_CREAT | O_WRONLY |
	O_TRUNC, 0666)) == -1)
		return (ft_perror(*filename));
	stop = safe_malloc(ft_strlen(*filename) + 1, where_err(LINE, FILE), info);
	src_i = -1;
	dst_i = 0;
	while ((*filename)[++src_i])
		if (!is_quo((*filename)[src_i]))
			stop[dst_i++] = (*filename)[src_i];
	stop[dst_i] = '\0';
	do_here_document(info, fd[(*cmd)->fd][0], stop, src_i == dst_i);
	ptr_free((void **)&stop);
	close(fd[(*cmd)->fd][0]);
	if ((fd[(*cmd)->fd][0] = open("./bonus/tmp", O_RDONLY)) == -1)
		return (ft_perror(*filename));
	*cmd = (*cmd)->next;
	return (true);
}

static bool	open_files(int **fd, t_cmdlst **cmd, char **filename,
				t_minishell *info)
{
	if ((*cmd)->type == OUTPUT || (*cmd)->type == DB_OUTPUT ||
			(*cmd)->type == INPUT)
		if (err_ambiguous_redirect(filename, info) == false)
			return (false);
	if ((*cmd)->type == OUTPUT || (*cmd)->type == DB_OUTPUT)
	{
		if ((fd[(*cmd)->fd][0] = open(*filename, O_CREAT | O_WRONLY |
			set_mode((*cmd)->type), 0666))
				== -1)
			return (ft_perror(*filename));
	}
	else if ((*cmd)->type == INPUT)
	{
		if ((fd[(*cmd)->fd][0] = open(*filename, O_RDONLY)) == -1)
			return (ft_perror(*filename));
	}
	else if ((*cmd)->type == DB_INPUT)
		when_here_document(fd, cmd, filename, info);
	return (true);
}

static int	check_last_redir_and_close_fd(int **fd, t_cmdlst *next_sep)
{
	int	next_fd;

	if (next_sep && (next_sep->type == OUTPUT || next_sep->type == DB_OUTPUT
			|| next_sep->type == INPUT))
	{
		next_fd = next_sep->fd;
		if (fd[next_fd][0] != -1)
			if (ft_close(&(fd[next_fd][0])) == false)
				return (-1);
	}
	return (true);
}

int	open_files_and_stock_fd(int **fd,
						t_cmdlst **cmd_lst, t_minishell *info)
{
	t_cmdlst	*next_sep;

	while (*cmd_lst && (*cmd_lst)->next)
	{
		next_sep = (*cmd_lst)->next->next;
		if (open_files(fd, cmd_lst, &((*cmd_lst)->next->arg[0]), info)
			== false)
			return (false);
		if (check_last_redir_and_close_fd(fd, next_sep) == -1)
			all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
		else
			*cmd_lst = (*cmd_lst)->next;
		if (next_sep && (next_sep->type == PIPE || next_sep->type == SEMICOLON))
		{
			return (true);
		}
	}
	return (true);
}

/*
** if (next_sep->type == PIPE)
** if (!(info->ptr_for_free = ft_strdup((*cmd_lst)->next->arg[0])))
** {
** if (close(fd[(*cmd_lst)->fd][0]) == -1)
** all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
** all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
** } -> 82 line
*/
