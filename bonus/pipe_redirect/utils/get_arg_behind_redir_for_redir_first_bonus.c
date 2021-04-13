/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg_behind_redir_for_redir_first_bonus.        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 10:13:59 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/13 14:03:24 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bonus_includes/minishell_bonus.h"

static int	arg_len(t_cmdlst *cmd)
{
	int		i;
	int		arg_num;

	arg_num = 0;
	while (cmd)
	{
		if (!(cmd->type == OUTPUT || cmd->type == DB_OUTPUT))
		{
			i = 0;
			while (cmd->arg[++i])
				arg_num++;
		}
		if (cmd->next == NULL || (cmd->next
				&& (cmd->next->type == PIPE || cmd->next->type == SEMICOLON)))
			break ;
		cmd = cmd->next;
	}
	return (arg_num);
}

static char	**make_arg(t_cmdlst *cmd, char **res)
{
	int		arg_i;
	int		i;

	arg_i = 0;
	while (cmd)
	{
		if (!(cmd->type == OUTPUT || cmd->type == DB_OUTPUT))
		{
			i = 0;
			while (cmd->arg[++i])
			{
				res[arg_i++] = cmd->arg[i];
				cmd->arg[i] = NULL;
			}
		}
		if (cmd->next == NULL || (cmd->next
				&& (cmd->next->type == PIPE || cmd->next->type == SEMICOLON)))
			break ;
		cmd = cmd->next;
	}
	res[arg_i] = NULL;
	return (res);
}

char	**get_arg_behind_redir_for_first(t_cmdlst *cmd,
					t_minishell *info)
{
	int			arg_num;
	char		**res;

	arg_num = arg_len(cmd->next);
	res = malloc(sizeof(char *) * (arg_num + 1));
	if (res == NULL)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	res = make_arg(cmd->next, res);
	return (res);
}
