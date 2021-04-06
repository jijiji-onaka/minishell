/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:51:59 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/06 10:42:59 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	clear_terminal(char *buf, t_string *command, t_minishell *info)
{
	char	*tmp;

	(void)buf;
	tmp = ft_strdup(command->str);
	if (tmp == NULL)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	delete_displayed_command(where_err(LINE, FILE), command, info);
	putstr_fd(info->key.clean, STDOUT, where_err(LINE, FILE), info);
	free(command->str);
	command->str = tmp;
	put_prompt(info);
	dup_pos(info->cursor.cur_pos, info->cursor.command_start_pos);
	dup_pos(info->cursor.select_pos, info->cursor.command_start_pos);
	dup_pos(info->cursor.command_end_pos, info->cursor.command_start_pos);
	display_command(command, info);
}
