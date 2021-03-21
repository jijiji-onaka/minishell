/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_envval_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 02:36:29 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/21 14:53:18 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell_bonus.h"

static int		envval_len(char *str)
{
	int	len;

	len = 0;
	while (*str)
	{
		if (is_quo(*str) || *str == '$')
			len += 2;
		len++;
		(str)++;
	}
	return (len);
}

static bool		only_hatena_or_doll(char *ptr, int *len, t_str *string)
{
	if (ptr[1] == '?')
	{
		*len += ft_numlen(g_signal.exit_status);
		string->prev_len = 2;
		return (true);
	}
	if (ptr[1] == '\0' || ptr[1] == ' ' || ptr[1] == '\\')
	{
		*len += 1;
		string->prev_len = 1;
		string->str = "$";
		return (true);
	}
	return (false);
}

int				envval_len_and_return_index(char *ptr, int *len,
			t_envlst *env, t_str *string)
{
	int		ret;
	int		j;
	char	*tmp;
	bool	flag;

	if (only_hatena_or_doll(ptr, len, string) == true)
		return (string->prev_len);
	tmp = NULL;
	j = 1;
	if (!ft_isdigit(ptr[1]))
		while (ptr[j] && (ft_isalnum(ptr[j]) || ptr[j] == '_'))
			j++;
	if (tmp == NULL && (tmp = search_env(ptr + 1, j - 1, env, (bool *)&flag)))
		ret = j;
	if (!flag)
		tmp = NULL;
	string->str = tmp;
	if (string->str)
		*len += envval_len(string->str);
	else
		ret = j;
	if (ft_isdigit(ptr[1]))
		ret++;
	string->prev_len = ret;
	return (ret);
}
