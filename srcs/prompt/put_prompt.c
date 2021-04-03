/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 00:41:03 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/03 18:27:27 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	get_prompt_position(t_minishell *info)
{
	get_window_size(info);
	// info->window.line_num = 0;
	get_cursor_position(info->window.command_start_pos, info);
}

void		put_prompt(t_minishell *info)
{
	char	*user_name;
	char	*working_dir;

	if (isatty(STDIN_FILENO) == false)
		return ;
	user_name = ft_getenv("USER", info->env, false);
	working_dir = info->current_dir_path;
	if (!user_name)
		user_name = "Who am I?";
	if (write(STDIN_FILENO, user_name, ft_strlen(user_name)) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (write(STDIN_FILENO, "\033[1m\x1b[35m (;;) \x1b[0m", 19) < 19)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (!working_dir)
		working_dir = "Where am I?";
	if (write(STDIN_FILENO, working_dir, ft_strlen(working_dir)) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (write(STDIN_FILENO, "\033[1m\x1b[35m (;;) > \x1b[0m", 21) < 21)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	get_prompt_position(info);
	info->window.prompt_len = info->window.command_start_pos[X] - 1;
}
