/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 04:50:53 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/21 14:07:20 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		sig_quit(int code)
{
	(void)code;
	if (g_signal.fork_pid_for_pipe == 0)
	{
		g_signal.exit_status = 131;
		return ;
	}
	if (g_signal.sig_sign == 1)
	{
		if (g_signal.fork_pid_for_pipe != -1 ||
			(g_signal.fork_pid_for_pipe == -1 && g_signal.fork_pid != -1))
			g_signal.exit_status = 131;
		else
			g_signal.exit_status = 0;
		if (!(g_signal.fork_pid == -1 && g_signal.fork_pid_for_pipe == -1))
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
	g_signal.reading = 0;
	g_signal.exit_status = 1;
}

void		sig_int(int code)
{
	(void)code;
	if (g_signal.fork_pid_for_pipe == 0)
	{
		g_signal.exit_status = 130;
		return ;
	}
	if (g_signal.sig_sign == 1)
	{
		if (g_signal.fork_pid_for_pipe != -1 ||
			(g_signal.fork_pid_for_pipe == -1 && g_signal.fork_pid != -1))
			g_signal.exit_status = 130;
		else if (g_signal.fork_pid_for_pipe == -1)
			g_signal.exit_status = 0;
		if (g_signal.fork_pid_for_pipe != 0)
			write(STDOUT_FILENO, "\n", 1);
	}
	else
		break_read();
}
