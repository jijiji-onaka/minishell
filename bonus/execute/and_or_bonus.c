/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 03:15:15 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/18 03:15:40 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

t_cmdlst		*do_and(t_cmdlst **cmd)
{
	if (g_signal.exit_status == 0)
		return (*cmd);
	while (*cmd)
	{
		if ((*cmd)->type == SEMICOLON || (*cmd)->type == DB_PIPE)
			return (*cmd);
		*cmd = (*cmd)->next;
	}
	return (*cmd);
}

t_cmdlst		*do_db_pipe(t_cmdlst **cmd)
{
	if (g_signal.exit_status != 0)
		return (*cmd);
	while (*cmd)
	{
		if ((*cmd)->type == SEMICOLON || (*cmd)->type == DB_AND)
			return (*cmd);
		*cmd = (*cmd)->next;
	}
	return (*cmd);
}
