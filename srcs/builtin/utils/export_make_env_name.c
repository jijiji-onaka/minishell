/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_make_env_name.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 02:47:49 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/18 20:19:53 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*make_env_name(char *arg, int *i, t_minishell *info)
{
	char	*res;
	int		len;

	len = 0;
	*i = -1;
	while (arg[++(*i)] && arg[(*i)] != '=' && arg[(*i)] != '+')
		if (!(arg[(*i)] == '\'' || arg[(*i)] == '\"'))
			len++;
	if (arg[(*i)] == '\0')
		return (NULL);
	if (!(res = malloc(sizeof(char) * (len + 1))))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	*i = 0;
	while (*arg && *arg != '=' && !(*arg == '+' && *(arg + 1) == '='))
	{
		if (!(*arg == '\'' || *arg == '\"'))
			res[(*i)++] = *arg;
		arg++;
	}
	res[*i] = '\0';
	return (res);
}
