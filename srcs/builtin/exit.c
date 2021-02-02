/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 18:24:30 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 17:03:53 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	normal_exit(t_minishell_info *info)
{
	all_free_minishell_info(info);
	exit(1);
}

static void	selected_code_exit(t_minishell_info *info, int exit_code,
				bool float_flag)
{
	if (float_flag)
		exit_code = 255;
	all_free_minishell_info(info);
	exit(exit_code % 256);
}

static void	fail_too_arg_exit(t_minishell_info *info)
{
	if (write(2, "minishell: exit: too many arguments\n", 36) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	g_signal.exit_status = 1;
	return ;
}

static void	non_numeric_exit(t_minishell_info *info, char *arg1)
{
	if (write(2, "minishell: exit: ", 17) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (ft_putstr_fd(arg1, 2) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (write(2, ": numeric argument required\n", 28) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	exit(255);
}

void		exec_exit(t_minishell_info *info)
{
	int		count;
	bool	numeric_arg_flag;
	char	**arg;

	arg = info->cmd_lst->arg;
	count = count_2d(arg);
	if (write(2, "\033[0Kexit\n", 9) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (arg[1] != NULL && ft_isdigit(arg[1][0]))
		numeric_arg_flag = true;
	if (count == 1)
		normal_exit(info);
	else if (count == 2 && numeric_arg_flag == true)
		selected_code_exit(info, ft_atoi(arg[1]), is_float(arg[1]));
	else if (numeric_arg_flag)
		fail_too_arg_exit(info);
	else
		non_numeric_exit(info, arg[1]);
}
