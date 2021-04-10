/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 23:43:32 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/08 08:20:12 by tjinichi         ###   ########.fr       */
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
	if (isatty(STDIN) == false)
		all_free_exit(info, ERR_ISATTY, __LINE__, __FILE__);
	term = ft_getenv("TERM", info->env, false);
	if (term == NULL)
		term = getenv("TERM");
	if (tgetent(buf, term) == false)
		all_free_exit(info, ERR_TGETENT, __LINE__, __FILE__);
}

void		initialize_term(t_minishell *info)
{
	tcgetattr(STDIN, &(info->terminal[ORIGINAL]));
	info->terminal[REPLICA] = info->terminal[ORIGINAL];
	info->terminal[REPLICA].c_lflag &= ~(ICANON | ECHO);

	//これにするとCtrl + Cをおそらくreadで読み込める
	// info->terminal[REPLICA].c_lflag &= ~(ECHO | ICANON | ISIG);

	info->terminal[REPLICA].c_cc[VMIN] = 1;
	info->terminal[REPLICA].c_cc[VTIME] = 0;
	tcsetattr(STDIN, TCSAFLUSH, &(info->terminal[REPLICA]));
	// tcsetattr(STDIN, TCSANOW, &(info->terminal[REPLICA]));

}

void	set_key(t_minishell *info)
{
	info->key.up = "\033[A";
	info->key.down = "\033[B";
	info->key.left = tgetstr("le", NULL);
	if (info->key.left == NULL)
		all_free_exit(info, ERR_TGETSTR, __LINE__, __FILE__);
	info->key.right = tgetstr("nd", NULL);
	if (info->key.right == NULL)
		all_free_exit(info, ERR_TGETSTR, __LINE__, __FILE__);
	info->key.clean_right = tgetstr("ce", NULL);
	if (info->key.clean_right == NULL)
		all_free_exit(info, ERR_TGETSTR, __LINE__, __FILE__);
	info->key.clean = tgetstr("cl", NULL);
	if (info->key.clean == NULL)
		all_free_exit(info, ERR_TGETSTR, __LINE__, __FILE__);
	info->key.cursor_save = tgetstr("sc", NULL);
	if (info->key.cursor_save == NULL)
		all_free_exit(info, ERR_TGETSTR, __LINE__, __FILE__);
	info->key.cursor_restore = tgetstr("rc", NULL);
	if (info->key.cursor_restore == NULL)
		all_free_exit(info, ERR_TGETSTR, __LINE__, __FILE__);
	info->key.cursor_invisible = tgetstr("vi", NULL);
	if (info->key.cursor_invisible == NULL)
		all_free_exit(info, ERR_TGETSTR, __LINE__, __FILE__);
	info->key.cursor_visible = tgetstr("ve", NULL);
	if (info->key.cursor_visible == NULL)
		all_free_exit(info, ERR_TGETSTR, __LINE__, __FILE__);
	info->key.scroll_up = tgetstr("sf", NULL);
	if (info->key.scroll_up == NULL || *(info->key.scroll_up) == '\0')
	{
		info->key.scroll_up = tgetstr("do", NULL);
		if (info->key.scroll_up == NULL || *(info->key.scroll_up) == '\0')
		{
			info->key.scroll_up = tgetstr("nl", NULL);
			if (info->key.scroll_up == NULL || *(info->key.scroll_up) == '\0')
				info->key.scroll_up = "\n";
		}
	}
	info->key.scroll_down = tgetstr("sr", NULL);
	info->key.delete_line = tgetstr("dl", NULL);
	if (info->key.delete_line == NULL)
		all_free_exit(info, ERR_TGETSTR, __LINE__, __FILE__);
	// info->key.beep_sound = "\a";
	// printf("[[[[[%s]]]]]\n", info->history.begin->command);
	info->key.color_change = "\x1b[38;5;106m\x1b[48;5;27m";
	// printf("[[[[[%s]]]]]\n", info->history.begin->command);
	info->key.color_reset = "\033[0m";
}

// if (!SF || !*SF)
// { /* this is what GNU Emacs does */
// 	SF = tgetstr("do", &p);
// 	if (!SF || !*SF)
// 	{
// 		SF = tgetstr("nl", &p);
// 		if (!SF || !*SF)
// 			SF = "\n";
// 	}
// }

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
	if (argc > 1 && ft_strcmp("--noediting", argv[1]) == 0)
		info.minishell_op_no_edit = true;
	info.minishell_op_c = false;
	if (signal(SIGQUIT, &sig_quit) == SIG_ERR)
		all_free_exit(&info, ERR_SIGNAL, __LINE__, __FILE__);
	if (signal(SIGINT, &sig_int) == SIG_ERR)
		all_free_exit(&info, ERR_SIGNAL, __LINE__, __FILE__);
	initialize_term(&info);
	get_current_term_and_tgetent(&info);
	// printf("[[[[[%s]]]]]\n", info.history->begin->command);
	set_key(&info);
	console_loop(&info);
	return (0);
}

// __attribute__((destructor))
// void end()
// {
// 	system("leaks minishell");
// }
