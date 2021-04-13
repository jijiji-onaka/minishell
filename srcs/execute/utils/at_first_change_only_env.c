/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_first_change_only_env.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 00:02:47 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/10 15:26:37 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	arg_num_len(t_cmdlst *cmd, t_minishell *info)
{
	int		i;
	int		arg_num;
	char	**tmp;

	i = -1;
	arg_num = 0;
	while (cmd->arg[++i])
	{
		if (!(cmd->type == EXPORT && cmd->arg[i][0] != '$')
			&& change_only_env(&(cmd->arg[i]), info))
		{
			tmp = split_each_arg(cmd->arg[i]);
			if (tmp == NULL)
				all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
			arg_num += count_2d(tmp);
			ptr_2d_free((void ***)&tmp, -1);
		}
		else
			arg_num++;
	}
	return (arg_num);
}

static char	**create_new_args(t_cmdlst *cmd, t_minishell *info)
{
	char	**new;
	char	**tmp;
	int		i[3];

	new = malloc((sizeof(char **) * (arg_num_len(cmd, info) + 1)));
	if (new == NULL)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	i[0] = -1;
	i[1] = 0;
	while (cmd->arg[++i[0]])
	{
		tmp = split_each_arg(cmd->arg[i[0]]);
		if (tmp == NULL)
			all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
		i[2] = 0;
		while (tmp[i[2]])
			new[i[1]++] = tmp[i[2]++];
		ptr_2d_free((void ***)&tmp, 0);
	}
	new[i[1]] = NULL;
	return (new);
}

bool	at_first_change_only_env(t_cmdlst *cmd, int *type,
					t_minishell *info)
{
	char	**new;

	(void)type;
	new = create_new_args(cmd, info);
	ptr_2d_free((void ***)&(cmd->arg), -1);
	cmd->arg = new;
	if (cmd->arg[0] == NULL || cmd->arg[0][0] == '\0')
		return (false);
	return (true);
}
