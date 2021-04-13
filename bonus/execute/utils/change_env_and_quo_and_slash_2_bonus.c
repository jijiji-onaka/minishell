/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env_and_quo_and_slash_2_bonus.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 16:46:27 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/13 14:03:24 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bonus_includes/minishell_bonus.h"

static char	return_back_slash_or_null(char chr[2], char *now)
{
	if (chr[B_SLA] == '\0' && *now == '\\')
		return ('\\');
	return ('\0');
}

void	fill_normal_with_slash_support(char *res, int *res_i, char chr[2],
														char *now)
{
	if (((*(now + 1)) == '\"' || *(now + 1) == '$') && *now == '\\'
		&& chr[B_SLA] == '\0' && chr[QUO] != '\'')
	{
		chr[B_SLA] = '\\';
		return ;
	}
	if (chr[QUO] == '\0' && chr[B_SLA] == '\0' && *now == '\\')
		chr[B_SLA] = '\\';
	else if (chr[QUO] != '\"')
	{
		if (!(*now == '\'' && chr[B_SLA] == '\\' && chr[QUO] == '\''))
			res[(*res_i)++] = *now;
		chr[B_SLA] =return_back_slash_or_null(chr, now);
	}
	else if (chr[QUO] == '\"')
	{
		if (*now != '\\' || (*now == '\\' && chr[B_SLA] == '\0'))
			res[(*res_i)++] = *now;
		if (*now == '\\' && chr[B_SLA] == '\0')
			chr[B_SLA] = '\\';
		else if (chr[B_SLA] == '\\')
			chr[B_SLA] = '\0';
	}
}

static void	normal_with_slash_support_len(int *len, char chr[2],
														char *now)
{
	if ((is_quo(*(now + 1)) || *(now + 1) == '$') && *now == '\\'
		&& chr[B_SLA] == '\0' && chr[QUO] != '\'')
	{
		chr[B_SLA] = '\\';
		return ;
	}
	if (chr[QUO] == '\0' && chr[B_SLA] == '\0' && *now == '\\')
		chr[B_SLA] = '\\';
	else if (chr[QUO] != '\"')
	{
		if (!(*now == '\'' && chr[B_SLA] == '\\' && chr[QUO] == '\''))
			(*len)++;
		chr[B_SLA] = return_back_slash_or_null(chr, now);
	}
	else if (chr[QUO] == '\"')
	{
		if (*now != '\\' || (*now == '\\' && chr[B_SLA] == '\0'))
			(*len)++;
		if (*now == '\\' && chr[B_SLA] == '\0')
			chr[B_SLA] = '\\';
		else if (chr[B_SLA] == '\\')
			chr[B_SLA] = '\0';
	}
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
		*len += ft_strlen(string->str);
	if (ft_isdigit(ptr[1]))
		i++;
	string->prev_len = i;
	return (i);
}

int	after_changed_len(char *ptr, t_minishell *info, t_str *string)
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
		else if ((ptr[arg_i] == '$'
				&& (ptr[arg_i + 1] != '\0' && ptr[arg_i + 1] != chr[QUO])
				&& (chr[B_SLA] == '\0') && !(chr[QUO] == '\'')))
			arg_i += envval_len_and_return_index(ptr + arg_i, &len,
					info->env, &(string[++struct_i])) - 1;
		else
			normal_with_slash_support_len(&len, chr, &ptr[arg_i]);
	}
	if (chr[B_SLA])
		len++;
	if (chr[QUO])
		len++;
	return (len);
}
