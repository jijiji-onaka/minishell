/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 00:41:03 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/04 03:30:46 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		put_prompt(t_minishell *info)
{
	char	*user_name;
	char	*working_dir;

	if (isatty(STDIN) == false)
		return ;
	user_name = ft_getenv("USER", info->env, false);
	working_dir = info->current_dir_path;
	if (!user_name)
		user_name = "Who am I?";
	putstr_fd(user_name, STDOUT, where_err(LINE, FILE), info);
	if (write(STDOUT, "\033[1m\x1b[35m (;;) \x1b[0m", 19) < 19)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (!working_dir)
		working_dir = "Where am I?";
	putstr_fd(working_dir, STDOUT, where_err(LINE, FILE), info);
	if (write(STDOUT, "\033[1m\x1b[35m (;;) > \x1b[0m", 21) < 21)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	get_window_size(info);
	get_cursor_position(info->cursor.command_start_pos, info);
	info->window.prompt_len = info->cursor.command_start_pos[X] - 1;
}
