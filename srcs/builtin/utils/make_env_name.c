/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 02:47:49 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/04 02:51:35 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*make_env_name(char *args, int *i, t_minishell_info *info)
{
	char	*res;

	*i = 0;
	while (args[*i] && args[*i] != '=')
		(*i)++;
	if (args[*i] == '\0')
		return (NULL);
	if (!(res = malloc((*i) + 1)))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	*i = -1;
	while (args[++(*i)] != '=')
		res[*i] = args[*i];
	res[*i] = '\0';
	return (res);
}
