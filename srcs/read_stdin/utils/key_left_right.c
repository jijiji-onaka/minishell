/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_left_right.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:49:37 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/29 16:50:07 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	move_cursor_left(char *buf, t_string *command, t_minishell *info)
{
	if (command->len == 0)
		return ;
	--command->len;
	ft_putstr_fd(buf, STDIN_FILENO);
}

void	move_cursor_right(char *buf, t_string *command, t_minishell *info)
{
	if (command->len == info->key.save_command_len)
		return ;
	++command->len;
	ft_putstr_fd(buf, STDIN_FILENO);
}
