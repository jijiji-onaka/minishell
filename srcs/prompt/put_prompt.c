/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 00:41:03 by tjinichi          #+#    #+#             */
/*   Updated: 2021/05/05 20:51:04 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	put_prompt(t_minishell *info)
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
	if (write(STDOUT, " \033[38;5;44m\x1b[1m42\x1b[0m ", 22) < 22)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (!working_dir)
		working_dir = "Where am I?";
	putstr_fd(working_dir, STDOUT, where_err(LINE, FILE), info);
	if (write(STDOUT, " \033[38;5;44m\x1b[1m>\x1b[0m ", 21) < 21)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	get_cursor_position(info->cursor.command_start_pos, info);
}

void	display_what_is_waiting_for(char chr, char **ptr1, char **ptr2,
					t_minishell *info)
{
	int		write_num;

	write_num = 1;
	if (chr == '\"')
		write_num = write(STDOUT, "dquote> ", 8);
	else if (chr == '\'')
		write_num = write(STDOUT, "quote> ", 7);
	else
		write_num = write(STDOUT, "normal command> ", 16);
	if (write_num < 0)
	{
		if (ptr1)
			ptr_free((void **)ptr1);
		if (ptr2)
			ptr_free((void **)ptr2);
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	}
	get_cursor_position(info->cursor.command_start_pos, info);
	dup_pos(info->cursor.cur_pos, info->cursor.command_start_pos);
	dup_pos(info->cursor.command_end_pos, info->cursor.command_start_pos);
}

char	*reset_prompt(char **ptr1, char **ptr2)
{
	if (ptr1)
		ptr_free((void **)ptr1);
	if (ptr2)
		ptr_free((void **)ptr2);
	return (NULL);
}
