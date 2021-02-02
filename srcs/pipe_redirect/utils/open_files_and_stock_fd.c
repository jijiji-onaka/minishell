/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files_and_stock_fd.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 01:15:42 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 17:37:32 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	set_mode(int type)
{
	if (type == OUTPUT)
		return (O_TRUNC);
	else if (type == DB_OUTPUT)
		return (O_APPEND);
	else if (type == STDERR_OUTPUT)
		return (O_TRUNC);
	else if (type == STDERR_DB_OUTPUT)
		return (O_APPEND);
	return (0);
}

static bool	open_files(int fd[2], int type, char *filename,
				t_minishell_info *info)
{
	int	mode;

	if (type == OUTPUT || type == DB_OUTPUT)
	{
		mode = set_mode(type);
		if ((fd[0] = open(filename, O_CREAT | O_WRONLY | mode, 0666)) == -1)
			all_free_exit(info, ERR_OPEN, __LINE__, __FILE__);
	}
	else if (type == INPUT)
	{
		if ((fd[1] = open(filename, O_RDONLY)) == -1)
		{
			if (errno == ENOENT)
				return (err_no_such_file_or_directory(filename, info));
			all_free_exit(info, ERR_OPEN, __LINE__, __FILE__);
		}
	}
	else if (type == STDERR_OUTPUT || type == STDERR_OUTPUT)
	{
		mode = set_mode(type);
		if ((fd[2] = open(filename, O_CREAT | O_WRONLY | mode, 0666)) == -1)
			all_free_exit(info, ERR_OPEN, __LINE__, __FILE__);
	}
	return (true);
}

static int	check_last_redir_and_close_fd(int fd[3], t_cmdlst *next_sep)
{
	if (next_sep && (next_sep->type == OUTPUT || next_sep->type == DB_OUTPUT))
	{
		if (fd[0] != -1)
			if (ft_close(&(fd[0])) == false)
				return (-1);
		if (fd[2] != -1)
			if (ft_close(&(fd[1])) == false)
				return (-1);
	}
	else if (next_sep && next_sep->type == INPUT)
		if (fd[1] != -1)
			if (ft_close(&(fd[1])) == false)
				return (-1);
	if (next_sep && (next_sep->type == STDERR_OUTPUT ||
				next_sep->type == STDERR_DB_OUTPUT))
	{
		if (fd[2] != -1)
			if (ft_close(&(fd[1])) == false)
				return (-1);
		if (fd[0] != -1)
			if (ft_close(&(fd[0])) == false)
				return (-1);
	}
	return (true);
}

void		just_open_file(t_minishell_info *info, t_cmdlst *cmd)
{
	int	fd;

	if ((fd = open(cmd->arg[1], O_CREAT | O_WRONLY | set_mode(cmd->type), 0666))
			== -1)
		all_free_exit(info, ERR_OPEN, __LINE__, __FILE__);
	if (close(fd) == -1)
		all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
}

int			open_files_and_stock_fd(int fd[3], int type,
						t_cmdlst **cmd_lst, t_minishell_info *info)
{
	t_cmdlst	*next_sep;

	while ((*cmd_lst)->next)
	{
		next_sep = (*cmd_lst)->next->next;
		if (open_files(fd, (*cmd_lst)->type, (*cmd_lst)->next->arg[0], info)
			== false)
			return (false);
		if (check_last_redir_and_close_fd(fd, next_sep) == -1)
			all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
		if (type != ECHO)
			*cmd_lst = skip_lst_and_free(cmd_lst, 1);
		else
			*cmd_lst = (*cmd_lst)->next;
		if (next_sep && (next_sep->type == PIPE || next_sep->type == SEMICOLON))
			return (true);
	}
	if (type != ECHO)
		free_alloc_ptr_in_cmd_lst(cmd_lst);
	return (true);
}
