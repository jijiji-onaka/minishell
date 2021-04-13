/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_what.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 16:39:52 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/11 13:18:21 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool	is_command_exit(char *cmd)
{
	if (ft_strcmp(cmd, "exit") == 0)
		return (true);
	return (false);
}

bool	is_quo(int c)
{
	return (c == '\'' || c == '\"');
}

bool	is_redir(int c)
{
	return (c == OUTPUT || c == DB_OUTPUT || c == INPUT);
}
