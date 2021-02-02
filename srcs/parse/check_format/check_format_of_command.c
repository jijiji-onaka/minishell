/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_format_of_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 00:05:31 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 17:47:00 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool	check_format_of_command(char ***grp, t_minishell_info *info)
{
	int	i;

	i = -1;
	while ((*grp)[++i])
	{
		if (i != 0 && (*grp)[i][0] == '|' && (*grp)[i][1] != '|'
					&& !(*grp)[i + 1])
		{
			info->cmd_lst_num = waiting_for_next_command(grp, i + 1, info);
			if (*grp == NULL)
				return (false);
			return (true);
		}
		if (is_output_format_error(grp, i, info) == false)
			return (false);
		if (is_pipe_format_error(grp, i, info) == false)
			return (false);
		if (is_semicolon_format_error(grp, i, info) == false)
			return (false);
	}
	info->cmd_lst_num = i;
	return (true);
}
