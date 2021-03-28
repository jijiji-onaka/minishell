/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 04:50:53 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/24 00:41:42 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

void		sig_quit(int code)
{
	(void)code;
	if (g_global.fork_pid_for_pipe == 0)
	{
		g_global.exit_status = 131;
		return ;
	}
	if (g_global.sig_sign == 1)
	{
		if (g_global.fork_pid_for_pipe != -1 ||
			(g_global.fork_pid_for_pipe == -1 && g_global.fork_pid != -1))
			g_global.exit_status = 131;
		else
			g_global.exit_status = 0;
		if (!(g_global.fork_pid == -1 && g_global.fork_pid_for_pipe == -1))
		{
			write(STDOUT_FILENO, "Quit: ", 6);
			ft_putnbr_fd(code, 2);
			write(STDOUT_FILENO, "\n", 1);
		}
	}
	else
		write(STDOUT_FILENO, "\b\b  \b\b ", 6);
}

static void	break_read(void)
{
	write(STDOUT_FILENO, "\b\b  \n", 5);
	close(STDIN_FILENO);
	g_global.reading = false;
	g_global.exit_status = 1;
}

void		sig_int(int code)
{
	(void)code;
	if (g_global.fork_pid_for_pipe == 0)
	{
		g_global.exit_status = 130;
		return ;
	}
	if (g_global.sig_sign == 1)
	{
		if (g_global.fork_pid_for_pipe != -1 ||
			(g_global.fork_pid_for_pipe == -1 && g_global.fork_pid != -1))
			g_global.exit_status = 130;
		else if (g_global.fork_pid_for_pipe == -1)
			g_global.exit_status = 0;
		if (g_global.fork_pid_for_pipe != 0)
			write(STDOUT_FILENO, "\n", 1);
	}
	else
		break_read();
}
