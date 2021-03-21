/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env_and_quo_and_slash_2_bonus.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 16:46:27 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/21 14:15:17 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell_bonus.h"

void		fill_normal_with_slash_support(char *res, int *res_i, char chr[2],
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
		chr[B_SLA] = ((!chr[B_SLA] && *now == '\\') ? '\\' : '\0');
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
		chr[B_SLA] = ((!chr[B_SLA] && *now == '\\') ? '\\' : '\0');
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

int			after_changed_len(char *ptr, t_minishell *info, t_str *string)
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
		else if ((ptr[arg_i] == '$' &&
				(ptr[arg_i + 1] != '\0' && ptr[arg_i + 1] != chr[QUO])
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
