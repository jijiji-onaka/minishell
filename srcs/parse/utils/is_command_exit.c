/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_command_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 16:39:52 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 17:26:29 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool	is_command_exit(char *cmd)
{
	if (cmd[0] == 'e' && cmd[1] == 'x' && cmd[2] == 'i' && cmd[3] == 't'
		&& cmd[4] == '\0')
		return (true);
	return (false);
}
