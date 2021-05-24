/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 23:43:32 by tjinichi          #+#    #+#             */
/*   Updated: 2021/05/22 14:07:07 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	initialize_global_variables(void)
{
	g_global.fork_pid = -1;
	g_global.fork_pid_for_pipe = -1;
	g_global.reading = false;
	g_global.sig_sign = 2;
}

static void	initialize_cmd_lst(t_minishell *info)
{
	skip_cmdlst(&(info->cmd_lst), -1, true);
	info->cmd_lst = NULL;
}

static void	console_loop(t_minishell *info)
{
	char	*command;

	while (true)
	{
		initialize_global_variables();
		put_prompt(info);
		command = read_command(info);
		if (command == NULL)
			;
		else if (parse_command(info, command) != false)
		{
			g_global.sig_sign = 1;
			execute_command_loop(info);
			initialize_cmd_lst(info);
		}
	}
}

static int	minishell_option_c(char *argv_2, t_minishell *info)
{
	t_string	command;
	char		quo;

	info->minishell_op_c = true;
	initialize_global_variables();
	command.str = ft_strdup(argv_2);
	command.len = ft_strlen(command.str);
	quo = '\0';
	if (is_valid_command_quotations(command.str, &quo) == false)
	{
		write(STDERR, SYNTAX_1, 54);
		write(STDERR, &(quo), 1);
		free(command.str);
		return (write(STDERR, "'\n", 2));
	}
	if (parse_command(info, command.str) != false)
	{
		g_global.sig_sign = 1;
		execute_command_loop(info);
		initialize_cmd_lst(info);
	}
	free(command.str);
	all_free_minishell_info(info);
	return (g_global.exit_status);
}

int	main(int argc, char **argv)
{
	t_minishell	info;

	set_minishell(&info);
	g_global.info = info;
	if (argc > 2 && ft_strncmp("-c", argv[1], 3) == 0)
		return (minishell_option_c(argv[2], &info));
	if (argc > 1 && ft_strcmp("--noediting", argv[1]) == 0)
		info.minishell_op_no_edit = true;
	info.minishell_op_c = false;
	if (signal(SIGQUIT, &sig_quit) == SIG_ERR)
		all_free_exit(&info, ERR_SIGNAL, __LINE__, __FILE__);
	if (signal(SIGINT, &sig_int) == SIG_ERR)
		all_free_exit(&info, ERR_SIGNAL, __LINE__, __FILE__);
	set_term(&info);
	console_loop(&info);
	return (0);
}

// __attribute__((destructor))
// void end()
// {
// 	system("leaks minishell");
// }
