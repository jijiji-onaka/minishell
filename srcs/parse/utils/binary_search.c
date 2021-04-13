/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_search.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 11:16:32 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/11 13:17:55 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	binary_search(char *cmd)
{
	int			ret;
	const char	*base[CMD_NUM] = {"\0", ";", "<", ">", ">>",
	"cd", "echo", "env", "export", "pwd", "unset", "|"};

	if (is_command_exit(cmd) == true)
		return (EXIT);
	if (ft_getenv("PATH", g_global.info.env, false) == NULL)
		ret = str_bsearch(cmd, base, CMD_NUM, ft_strcmp);
	else
		ret = str_bsearch(cmd, base, CMD_NUM, strcmp_regardless_of_case);
	if (ret == NOT_CMD)
		return (BIN);
	return (ret);
}
