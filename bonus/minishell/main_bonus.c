/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 23:43:32 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/20 01:22:57 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

static void	initialize_global_variables(void)
{
	g_signal.fork_pid = -1;
	g_signal.fork_pid_for_pipe = -1;
	g_signal.reading = false;
}

static void	initialize_cmd_lst(t_minishell *info)
{
	skip_cmdlst(&(info->cmd_lst), -1, true);
	info->cmd_lst = NULL;
}

static void	console_loop(t_minishell *info)
{
	char	*command;

	while (1)
	{
		initialize_global_variables();
		put_prompt(info);
		g_signal.sig_sign = 2;
		if ((command = waiting_for_input(info)) != NULL)
		{
			if (parse_command(info, command) != false)
			{
				g_signal.sig_sign = 1;
				execute_command_loop(info);
				initialize_cmd_lst(info);
			}
		}
	}
}

int			main(void)
{
	t_minishell	info;

	display_welcome_message();
	set_minishell(&info);
	set_shell_level();
	set_env(&info);
	if (!(info.current_dir_path = ft_strdup(search_env("PWD", 3, info.env))))
		all_free_exit(&info, ERR_MALLOC, __LINE__, __FILE__);
	g_signal.info = info;
	g_signal.sig_sign = 1;
	if (signal(SIGQUIT, &sig_quit) == SIG_ERR)
		all_free_exit(&info, ERR_SIGNAL, __LINE__, __FILE__);
	if (signal(SIGINT, &sig_int) == SIG_ERR)
		all_free_exit(&info, ERR_SIGNAL, __LINE__, __FILE__);
	console_loop(&info);
	return (0);
}
