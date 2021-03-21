/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg_behind_redir.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 09:51:09 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/18 05:13:48 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	arg_len(t_cmdlst *cmd)
{
	int		i;
	int		arg_num;
	char	**args;

	args = cmd->arg;
	arg_num = -1;
	while (args && args[++arg_num])
		;
	cmd = cmd->next;
	while (cmd)
	{
		if (!(cmd->type == OUTPUT || cmd->type == DB_OUTPUT))
		{
			i = 0;
			while (cmd->arg[++i])
				arg_num++;
		}
		if (cmd->next == NULL || (cmd->next && (cmd->next->type == PIPE ||
					cmd->next->type == SEMICOLON)))
			break ;
		cmd = cmd->next;
	}
	return (arg_num);
}

static char	**make_arg(t_cmdlst *cmd, char **res)
{
	int		arg_i;
	int		i;

	arg_i = -1;
	while (cmd->arg && cmd->arg[++arg_i])
		res[arg_i] = cmd->arg[arg_i];
	cmd = cmd->next;
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
		if (cmd->next == NULL || (cmd->next && (cmd->next->type == PIPE ||
					cmd->next->type == SEMICOLON)))
			break ;
		cmd = cmd->next;
	}
	res[arg_i] = NULL;
	return (res);
}

void		get_arg_behind_redir(t_cmdlst *cmd, t_minishell *info)
{
	int			arg_num;
	char		**res;

	if (cmd->arg == NULL)
		return ;
	arg_num = arg_len(cmd);
	if (!(res = malloc((size_t)sizeof(char *) * (arg_num + 1))))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	res = make_arg(cmd, res);
	ptr_2d_free((void***)&cmd->arg, 0);
	cmd->arg = res;
}
