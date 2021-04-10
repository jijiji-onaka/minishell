/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 04:06:27 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/09 12:24:45 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

static int	err_fd(long long fd, t_minishell *info)
{
	if (fd > INT_MAX)
	{
		if (write(STDERR,
"minishell: file descriptor out of range: Bad file descriptor\n", 61) < 0)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	}
	else if (fd >= 256 && fd <= INT_MAX)
	{
		if (write(STDERR, "minishell: ", 11) < 0)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
		if (ft_putnbr_fd(fd, STDERR) == false)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
		if (write(STDERR, ": Bad file descriptor\n", 22) < 0)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	}
	g_global.exit_status = EXIT_FAILURE;
	return (-1);
}

static int	check_redirect_fd(t_minishell *info, char **command)
{
	int			i;
	long long	fd;

	if (**command == '<' || ft_strcmp(*command, "<<") == 0)
		return (0);
	else if (!ft_isdigit(**command))
		return (1);
	i = -1;
	fd = 0;
	while ((*command)[++i])
	{
		if (!ft_isdigit((*command)[i]))
			break ;
		fd = fd * 10 + ((*command)[i] - '0');
	}
	if (!((*command)[i] == '>' || (*command)[i] == '<'))
		return (1);
	*command = *command + i;
	if (fd > INT_MAX || fd >= 256 && fd <= INT_MAX)
		return (err_fd(fd, info));
	return (fd);
}

static bool	check_quotation(char **command, t_minishell *info)
{
	char	quo;

	quo = '\0';
	if (is_valid_quotations(command, &quo) == false)
		if (waiting_for_quotation(quo, command, info) == false)
			return (false);
	return (true);
}

static int	parsing(t_minishell *info, char **command)
{
	int			type;
	char		**split;
	char		*begin;
	int			fd_for_redir;

	if ((*command)[0] == ';')
		return (cmdlst_add_back(info, NULL, SEMICOLON, 0));
	if (check_quotation(command, info) == false)
		return (false);
	begin = *command;
	if ((fd_for_redir = check_redirect_fd(info, &(*command))) == -1)
	{
		*command = begin;
		return (false);
	}
	if (!(split = split_each_arg((*command))))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	*command = begin;
	if (split[0] == NULL)
		return (true);
	type = binary_search(split[0]);
	if (is_redir(type))
		return (cmdlst_add_back(info, split, type, fd_for_redir));
	return (cmdlst_add_back(info, split, type, 0));
}

bool		parse_command(t_minishell *info, char *command)
{
	char	**cmd_grp;
	char	*tmp;
	int		i;
	bool	ret;

	info->ptr_for_free = command;
	tmp = skip_space(command);
	if (!(cmd_grp = split_each_parts(tmp)))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	ptr_free((void **)&(command));
	info->ptr_for_free = NULL;
	cmd_grp = rm_spaces_in_2d_array(cmd_grp, info);
	if (check_syntax(&cmd_grp, info) == false)
		return (false);
	info->ptr_2d_for_free = cmd_grp;
	i = -1;
	ret = true;
	while (cmd_grp[++i])
		if (ret == true)
			ret = parsing(info, &(cmd_grp[i]));
	ptr_2d_free((void ***)&cmd_grp, i);
	info->ptr_2d_for_free = NULL;
	return (ret);
}
