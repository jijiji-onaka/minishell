/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_back_command_lst.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 16:27:50 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 17:27:10 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static t_cmdlst	*cmd_lstlast(t_cmdlst *lst)
{
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

/*
** parseする時に(add_pwd_to_lst等)、後ろにリストをつなげる関数
*/

static void		cmd_lstadd_back(t_cmdlst **begin, t_cmdlst *new)
{
	t_cmdlst *last;

	if (!*begin)
	{
		*begin = new;
		return ;
	}
	last = cmd_lstlast(*begin);
	last->next = new;
}

void			add_back_command_lst(t_minishell_info *info,
						char **command, int type)
{
	t_cmdlst	*cmd;

	if (!(cmd = malloc(sizeof(t_cmdlst))))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	if (type == CMD_NUM)
		cmd->type = NOT_CMD;
	else if (type == OUTPUT_PIPE)
		cmd->type = OUTPUT;
	else
		cmd->type = type;
	cmd->arg = command;
	cmd->next = NULL;
	cmd_lstadd_back(&(info->cmd_lst), cmd);
}
