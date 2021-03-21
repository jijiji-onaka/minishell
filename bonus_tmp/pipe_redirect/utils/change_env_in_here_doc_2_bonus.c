/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env_in_here_doc_2_bonus.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 13:24:41 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/20 13:27:40 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell_bonus.h"

void		fill_normal_with_slash_support__(char *res, int *res_i, char chr[2],
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

int			after_changed_len__(char *ptr, t_minishell *info, t_str *string)
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
				&& (chr[B_SLA] == '\0')))
			arg_i += envval_len_and_return_index(ptr + arg_i, &len,
				info->env, &(string[++struct_i])) - 1;
		else
			normal_with_slash_support_len(&len, chr, &ptr[arg_i]);
	}
	return (len);
}
