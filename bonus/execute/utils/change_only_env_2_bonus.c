/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_only_env_2_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:09:33 by tjinichi          #+#    #+#             */
/*   Updated: 2021/05/22 13:37:15 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bonus_includes/minishell_bonus.h"

void	fill_normal_with_slash_support_(char *res, int *res_i, char chr[2],
														char *now)
{
	if (*now == '\\')
	{
		if (chr[B_SLA] == '\0' && !(*(now + 1) == '\"' || *(now + 1) == '\''))
		{
			chr[B_SLA] = '\\';
		}
		else
			chr[B_SLA] = '\0';
		res[(*res_i)++] = *now;
		return ;
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
		if (chr[B_SLA] == '\0' && !(*(now + 1) == '\"' || *(now + 1) == '\''))
		{
			chr[B_SLA] = '\\';
		}
		else
			chr[B_SLA] = '\0';
		(*len)++;
		return ;
	}
	else
		chr[B_SLA] = '\0';
	(*len)++;
}

bool	only_hatena_or_doll(char *ptr, int *len, t_str *string)
{
	if (ptr[1] == '?')
	{
		*len += ft_numlen(g_global.exit_status);
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
	int		i;
	char	*env_value;
	char	tmp_chr;

	if (only_hatena_or_doll(ptr, len, string) == true)
		return (string->prev_len);
	i = 1;
	if (!ft_isdigit(ptr[1]))
		while (ptr[i] && (ft_isalnum(ptr[i]) || ptr[i] == '_'))
			i++;
	tmp_chr = ptr[i];
	ptr[i] = '\0';
	env_value = ft_getenv(ptr + 1, env, true);
	ptr[i] = tmp_chr;
	string->str = env_value;
	if (string->str)
		*len += envval_len(string->str);
	if (ft_isdigit(ptr[1]))
		i++;
	string->prev_len = i;
	return (i);
}

int	after_changed_len_(char *ptr, t_minishell *info, t_str *string)
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
		if ((ptr[arg_i] == '$'
				&& (ptr[arg_i + 1] != '\0' && ptr[arg_i + 1] != chr[QUO])
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
