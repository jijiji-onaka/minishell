/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_search_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 11:16:32 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/13 14:28:50 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bonus_includes/minishell_bonus.h"

int	binary_search(char *cmd)
{
	int			ret;
	const char	*base[CMD_NUM] = {"\0", "&&", ";", "<", "<<", ">", ">>",
	"cd", "echo", "env", "export", "pwd", "unset", "|", "||"};

	if (is_command_exit(cmd) == true)
		return (EXIT);
	if (ft_getenv("PATH", g_global.info.env, false) == NULL)
		ret = str_bsearch(cmd, base, CMD_NUM, ft_strcmp);
	else
		ret = str_bsearch(cmd, base, CMD_NUM, strcmp_regardless_of_case);
	if (ret == NOT_CMD)
		return (BIN);
	else if (ret == DB_INPUT_)
		return (DB_INPUT);
	else if (ret == DB_PIPE_)
		return (DB_PIPE);
	return (ret);
}
