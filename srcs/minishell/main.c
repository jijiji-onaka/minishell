/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 23:43:32 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/28 22:43:14 by tjinichi         ###   ########.fr       */
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
		if ((command = waiting_for_input(info)) == NULL)
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
	char	*command;

	info->minishell_op_c = true;
	initialize_global_variables();
	if (!(command = ft_strdup(argv_2)))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	if (parse_command(info, command) != false)
	{
		g_global.sig_sign = 1;
		execute_command_loop(info);
		initialize_cmd_lst(info);
	}
	all_free_minishell_info(info);
	return (g_global.exit_status);
}

void	get_current_term_and_tgetent(t_minishell *info)
{
	char	*term;
	char	buf[1024];

	ft_bzero(buf, 1024);
	if (isatty(STDIN_FILENO) == false)
		all_free_exit(info, ERR_ISATTY, __LINE__, __FILE__);
	term = ft_getenv("TERM", info->env, false);
	if (term == NULL)
		term = getenv("TERM");
	if (tgetent(buf, term) == false)
		all_free_exit(info, ERR_TGETENT, __LINE__, __FILE__);
}

void		initialize_term(void)
{
	tcgetattr(STDIN_FILENO, &(g_global.terms[ORIGINAL]));
	g_global.terms[REPLICA] = g_global.terms[ORIGINAL];
	g_global.terms[REPLICA].c_lflag &= ~(ICANON | ECHO);
	g_global.terms[REPLICA].c_cc[VMIN] = 1;
	g_global.terms[REPLICA].c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &(g_global.terms[REPLICA]));
	// ft_putstr_fd(tgetstr("ti", NULL), STDIN_FILENO);
	// ft_putstr_fd(tgetstr("vi", NULL), STDIN_FILENO);
	// display_welcome_message();
	// char buf[1024];
	// ft_bzero(buf, 1024);
	// struct winsize winsize;
	// ioctl(STDIN_FILENO, TIOCGWINSZ, &winsize);
	// ft_putstr_fd(tgetstr("cl", NULL), STDIN_FILENO);
}

void	set_key(t_minishell *info)
{
	info->key.left = tgetstr("le", NULL);
	// info->key.left = init_key(2);
	if (info->key.left == NULL)
		all_free_exit(info, ERR_TGETSTR, __LINE__, __FILE__);
	// right yet
	info->key.right = tgetstr("nd", NULL);
	if (info->key.right == NULL)
		all_free_exit(info, ERR_TGETSTR, __LINE__, __FILE__);
	info->key.clean_right = tgetstr("ce", NULL);
	if (info->key.clean_right == NULL)
		all_free_exit(info, ERR_TGETSTR, __LINE__, __FILE__);
	info->key.save = tgetstr("sc", NULL);
	if (info->key.save == NULL)
		all_free_exit(info, ERR_TGETSTR, __LINE__, __FILE__);
	info->key.reset = tgetstr("rc", NULL);
	if (info->key.reset == NULL)
		all_free_exit(info, ERR_TGETSTR, __LINE__, __FILE__);
}

int			main(int argc, char **argv)
{
	t_minishell	info;

	set_minishell(&info);
	// set_shell_level();
	// set_env(&info);
	// if (!(info.current_dir_path = getcwd(NULL, 0)))
	// 	all_free_exit(&info, ERR_MALLOC, __LINE__, __FILE__);
	// if (!(info.oldpwd_path = ft_strdup(search_env("OLDPWD", 6, info.env, 0))))
	// 	all_free_exit(&info, ERR_MALLOC, __LINE__, __FILE__);


	// t_envlst *begin = info.env;
	// while (info.env)
	// {
	// 	if (strncmp("SHLVL", info.env->env.key.str, 5) == 0)
	// 	{
	// 		printf("key : [%s]\n", info.env->env.key.str);
	// 		printf("value : [%s]\n", info.env->env.value.str);
	// 	}
	// 	info.env = info.env->next;
	// }
	// info.env = begin;
	// exit(0);


	g_global.info = info;
	if (argc > 2 && ft_strncmp("-c", argv[1], 3) == 0)
		return (minishell_option_c(argv[2], &info));
	info.minishell_op_c = false;
	if (signal(SIGQUIT, &sig_quit) == SIG_ERR)
		all_free_exit(&info, ERR_SIGNAL, __LINE__, __FILE__);
	if (signal(SIGINT, &sig_int) == SIG_ERR)
		all_free_exit(&info, ERR_SIGNAL, __LINE__, __FILE__);
	initialize_term();
	get_current_term_and_tgetent(&info);
	set_key(&info);
	console_loop(&info);
	return (0);
}

// __attribute__((destructor))
// void end()
// {
// 	system("leaks minishell");
// }
