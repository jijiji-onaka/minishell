/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 23:43:32 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/27 19:32:25 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** info.current_dir_path = getcwd(NULL, 0); は
** pwdのためにカレントディレクトリを取得して構造体に入れている
** pwd ; pwdみたいな時に二回getcwd呼ぶの嫌だったのでそうした
*/

void		console_loop(t_minishell_info *info)
{
	char	*command;

	put_prompt(info);
	while (1)
	{
		if ((command = waiting_for_input(info)) == NULL)
			;
			// write(1, "\033[0K", 4); //これいらないかも、なんで書いたのか忘れた
		else
			if (parse_command(info, command) != false)
				execute_each_command_loop(info);
		put_prompt(info);
	}
}

int			main()
{
	t_minishell_info	info;

	display_welcome_message();
	// put_help_message();
	set_shell_level();
	set_minishell_info(&info);
	set_env(&info);
	set_prompt_message(info.env);
	signal(SIGQUIT, &sig_quit);
	signal(SIGINT, &sig_int);
	console_loop(&info);
}
