/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_only_env_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:09:33 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/21 14:13:29 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void		fill_normal_with_slash_support_(char *res, int *res_i, char chr[2],
														char *now)
{
	if (*now == '\\')
	{
		if (chr[B_SLA] == '\0')
			chr[B_SLA] = '\\';
		else
			chr[B_SLA] = '\0';
	}
	else
		chr[B_SLA] = '\0';
	res[(*res_i)++] = *now;
}

static void	normal_with_slash_support_len(int *len, char chr[2],
														char *now)
{
	if (*now == '\\')
	{
		if (chr[B_SLA] == '\0')
			chr[B_SLA] = '\\';
		else
			chr[B_SLA] = '\0';
	}
	else
		chr[B_SLA] = '\0';
	(*len)++;
}

bool		only_hatena_or_doll(char *ptr, int *len, t_str *string)
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

static int	envval_len_and_return_index(char *ptr, int *len,
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

int			after_changed_len_(char *ptr, t_minishell *info, t_str *string)
{
	char	chr[2];
	int		len;
	int		arg_i;
	int		struct_i;

	preparation__(&arg_i, &len, &struct_i, chr);
	while (ptr[++arg_i])
	{
		if (chr[B_SLA] == '\0' && chr[QUO] == '\0' && is_quo(ptr[arg_i]))
			chr[QUO] = ptr[arg_i];
		else if (chr[B_SLA] == '\0' && chr[QUO] == ptr[arg_i])
			chr[QUO] = '\0';
		if ((ptr[arg_i] == '$' &&
				(ptr[arg_i + 1] != '\0' && ptr[arg_i + 1] != chr[QUO])
				&& (chr[B_SLA] == '\0') && chr[QUO] == '\0'))
			arg_i += envval_len_and_return_index(ptr + arg_i, &len,
				info->env, &(string[++struct_i])) - 1;
		else
			normal_with_slash_support_len(&len, chr, &ptr[arg_i]);
	}
	if (chr[QUO])
		len++;
	if (chr[B_SLA])
		len++;
	return (len);
}
