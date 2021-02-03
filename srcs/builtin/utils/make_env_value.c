/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 20:41:03 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/03 21:18:29 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	env_value_len(char **args, int i, int j)
{
	int	len;

	len = 0;
	while ((args[j] + i)[len])
		len++;
	while (args[++j])
	{
		len++;
		i = 0;
		while (args[j][i] && args[j][i] != '=')
			i++;
		if (args[j][i] != '\0')
			break ;
		if (args[j + 1] == NULL && (len++))
			break ;
		len += i;
	}
	return (len);
}

char		*make_env_value(char **args, int i, int *j, t_minishell_info *info)
{
	int		len;
	char	*res;

	if (!(res = malloc(env_value_len(args, i, *j) + 1)))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	len = -1;
	while ((args[*j] + i)[++len])
		res[len] = (args[*j] + i)[len];
	while (args[++(*j)])
	{
		res[len++] = ' ';
		i = -1;
		while (args[*j][++i] && args[*j][i] != '=')
			res[len + i] = args[*j][i];
		if (args[*j][i] != '\0')
			break ;
		if (args[*j + 1] == NULL && (len++))
			break ;
		len += i;
	}
	res[len] = '\0';
	(*j)--;
	return (res);
}
