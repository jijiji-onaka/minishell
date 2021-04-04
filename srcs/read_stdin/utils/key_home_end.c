/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_home_end.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 03:56:08 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/04 06:01:56 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	go_command_beginning(char *buf, t_string *command, t_minishell *info)
{
	size_t	i;
	size_t	len;
	char	*left;

	len = command->len;
	left = info->key.left;
	i = 0;
	while (i < len)
	{
		move_cursor_left(buf, command, info);
		i++;
	}
}

void	go_command_end(char *buf, t_string *command, t_minishell *info)
{
	size_t	i;
	size_t	len;
	char	*right;

	i = command->len;
	right = info->key.right;
	len = info->key.save_command_len;
	while (i < len)
	{
		move_cursor_right(buf, command, info);
		i++;
	}
}
