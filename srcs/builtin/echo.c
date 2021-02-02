/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 00:04:05 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 17:39:11 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	put_newline(t_minishell_info *info)
{
	if (write(1, "\n", 1) == -1)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	return ;
}

static void	putstr_space(char *s, t_minishell_info *info)
{
	if (write(STDOUT_FILENO, s, ft_strlen(s)) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (write(STDOUT_FILENO, " ", 1) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
}

static void	put_all_first_arg(int i, t_cmdlst *cmd, t_minishell_info *info)
{
	if (cmd->arg[i] != NULL)
		putstr_space(cmd->arg[i], info);
	cmd = cmd->next;
	while (cmd)
	{
		if (cmd->type == OUTPUT || cmd->type == DB_OUTPUT)
			;
		else
		{
			if (cmd->arg[1] != NULL)
				putstr_space(cmd->arg[1], info);
			if ((cmd->next == NULL && i != 2) || (cmd->next && i != 2 &&
				(cmd->next->type == PIPE || cmd->next->type == SEMICOLON)))
				if (write(1, "\n", 1) == -1)
					all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
		}
		if (cmd->next == NULL || (cmd->next && (cmd->next->type == PIPE ||
					cmd->next->type == SEMICOLON)))
			break ;
		cmd = skip_lst_and_free(&cmd, 1);
	}
}

void		exec_echo(t_minishell_info *info, t_cmdlst *cmd)
{
	int			i;
	char		**args;
	int			n_flag;

	args = cmd->arg;
	n_flag = 0;
	if (args[1] != NULL && args[1][0] == '-' && ft_strcmp(args[1], "-n") == 0)
		n_flag = 1;
	i = 1 + n_flag;
	if (cmd->next && (cmd->next->type == OUTPUT ||
				cmd->next->type == DB_OUTPUT))
		return (put_all_first_arg(i, cmd, info));
	if (args[1] == NULL)
		return (put_newline(info));
	if (n_flag == true)
		return (error_mandatory(ERR_ECHO, 21, info));
	while (args[i])
	{
		if (ft_putstr_fd(args[i], 1) == false)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
		putstr_space(args[i], info);
		if (args[i + 1] == NULL && n_flag == 0)
			put_newline(info);
		i++;
	}
}
