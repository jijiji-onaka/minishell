/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 23:43:32 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/21 20:16:54 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	initialize_global_variables(void)
{
	g_signal.fork_pid = -1;
	g_signal.fork_pid_for_pipe = -1;
	g_signal.reading = false;
	g_signal.sig_sign = 2;
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

static int	minishell_option_c(char *argv_2, t_minishell *info)
{
	char	*command;

	info->minishell_op_c = true;
	initialize_global_variables();
	if (!(command = ft_strdup(argv_2)))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	if (parse_command(info, command) != false)
	{
		g_signal.sig_sign = 1;
		execute_command_loop(info);
		initialize_cmd_lst(info);
	}
	all_free_minishell_info(info);
	return (g_signal.exit_status);
}

int			main(int argc, char **argv)
{
	t_minishell	info;

	display_welcome_message();
	set_minishell(&info);
	set_shell_level();
	set_env(&info);
	if (!(info.current_dir_path = getcwd(NULL, 0)))
		all_free_exit(&info, ERR_MALLOC, __LINE__, __FILE__);
	if (!(info.oldpwd_path = ft_strdup(search_env("OLDPWD", 6, info.env, 0))))
		all_free_exit(&info, ERR_MALLOC, __LINE__, __FILE__);
	g_signal.info = info;
	if (argc > 2 && ft_strncmp("-c", argv[1], 3) == 0)
		return (minishell_option_c(argv[2], &info));
	info.minishell_op_c = false;
	if (signal(SIGQUIT, &sig_quit) == SIG_ERR)
		all_free_exit(&info, ERR_SIGNAL, __LINE__, __FILE__);
	if (signal(SIGINT, &sig_int) == SIG_ERR)
		all_free_exit(&info, ERR_SIGNAL, __LINE__, __FILE__);
	console_loop(&info);
	return (0);
}
