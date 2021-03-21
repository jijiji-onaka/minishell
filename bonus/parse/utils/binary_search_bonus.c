/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_search_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 03:43:49 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/18 03:14:25 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell_bonus.h"

int		binary_search(char *cmd)
{
	const char	*base[CMD_NUM] = {"\0", "&&", ";", "<", "<<", ">", ">>",
	"cd", "echo", "env", "export", "pwd", "unset", "|", "||"};
	int			ret;

	if (is_command_exit(cmd) == true)
		return (EXIT);
	if (search_env("PATH", 4, g_signal.info.env) == NULL)
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
