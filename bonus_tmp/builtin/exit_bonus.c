/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 18:24:30 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/20 01:28:00 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

static void	normal_exit(t_minishell *info)
{
	all_free_minishell_info(info);
	exit(g_signal.exit_status);
}

static void	fail_too_arg_exit(t_minishell *info)
{
	if (write(2, "minishell: exit: too many arguments\n", 36) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	g_signal.exit_status = 1;
	info->exit_too_arg = true;
	return ;
}

static void	non_numeric_exit(t_minishell *info, char *arg1)
{
	if (write(2, "minishell: exit: ", 17) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (ft_putstr_fd(arg1, 2) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (write(2, ": numeric argument required\n", 28) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	g_signal.exit_status = 255;
	exit(g_signal.exit_status);
}

static void	selected_code_exit(t_minishell *info, int exit_code)
{
	all_free_minishell_info(info);
	g_signal.exit_status = exit_code % 256;
	exit(g_signal.exit_status);
}

void		exec_exit(t_minishell *info, t_cmdlst *cmd)
{
	bool		numeric_arg_flag;

	if (!(cmd->checker_pipe) && !(cmd->checker_redir))
		if (write(2, "\033[0Kexit\n", 9) < 0)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (cmd->arg[1] == NULL)
		normal_exit(info);
	numeric_arg_flag = set_numeric_flag(cmd->arg[1]);
	if (cmd->arg[1] == NULL)
		normal_exit(info);
	else if (cmd->arg[2] == NULL && numeric_arg_flag == true)
		selected_code_exit(info, ft_atoi(cmd->arg[1]));
	else if (numeric_arg_flag)
		fail_too_arg_exit(info);
	else
		non_numeric_exit(info, cmd->arg[1]);
}
