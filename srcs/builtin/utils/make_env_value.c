/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 20:41:03 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/04 02:55:17 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	count(char **args, int i, int j)
{
	char	quo;
	int		len;
	int		k;

	len = 0;
	quo = (args[j] + i)[len];
	while ((args[j] + i)[len])
		len++;
	k = 0;
	while (args[++j])
	{
		len++;
		while (args[j][k] && args[j][k] != quo)
			k++;
		len += k;
		if (args[j][k] == quo)
			break ;
	}
	return (len);
}

static char	*quotation(char **args, int i, int *j, t_minishell_info *info)
{
	char	quo;
	int		len;
	int		k;
	char	*res;

	if (!(res = malloc(count(args, i, *j) + 1)))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	quo = (args[*j] + i)[0];
	len = -1;
	while ((args[*j] + i)[++len + 1])
		res[len] = (args[*j] + i)[len + 1];
	while (args[++*j] && (res[len++] = ' '))
	{
		k = -1;
		while (args[*j][++k] && args[*j][k] != quo)
			res[len + k] = args[*j][k];
		len += k;
		if (args[*j][k] == quo)
			break ;
	}
	res[len] = '\0';
	return (res);
}

char		*make_env_value(char **args, int i, int *j, t_minishell_info *info)
{
	int		len;
	char	*res;

	if (*(args[*j] + i) == '\'' || *(args[*j] + i) == '\"')
		return (quotation(args, i, j, info));
	len = 0;
	i++;
	while ((args[*j] + i)[len])
		len++;
	if (!(res = malloc(len + 1)))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	len = -1;
	while ((args[*j] + i)[++len])
		res[len] = (args[*j] + i)[len];
	res[len] = '\0';
	return (res);
}
