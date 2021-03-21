/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env_in_here_doc_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 13:23:16 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/20 13:28:12 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell_bonus.h"

static void	stock_envval(char *res, char *str, int *res_i)
{
	while (*(str))
	{
		if (*(str) == '\"')
			res[(*res_i)++] = '\'';
		else if (*(str) == '\'')
			res[(*res_i)++] = '\"';
		else if (*str == '$')
			res[(*res_i)++] = '\'';
		if (*(str) != '\0')
			res[(*res_i)++] = *(str);
		if (*(str) == '\"')
			res[(*res_i)++] = '\'';
		else if (*(str) == '\'')
			res[(*res_i)++] = '\"';
		else if (*str == '$')
			res[(*res_i)++] = '\'';
		(str)++;
	}
}

static int	stock_envval_and_return_index(char *str, char next_chr,
					int *res_i, t_str *string)
{
	int	num_len;
	int	tmp_num;
	int	tmp_num_len;

	if (next_chr == '?')
	{
		tmp_num = g_signal.exit_status;
		num_len = ft_numlen(tmp_num);
		tmp_num_len = num_len;
		while (tmp_num_len)
		{
			str[(*res_i) + tmp_num_len - 1] = tmp_num % 10 + '0';
			tmp_num /= 10;
			tmp_num_len--;
		}
		(*res_i) += num_len;
	}
	else if (string->str)
		stock_envval(str, string->str, res_i);
	return (string->prev_len);
}

static void	fill_in_return_str(char *res, char **ptr, t_str *string)
{
	char	chr[2];
	int		arg_i;
	int		res_i;
	int		struct_i;

	preparation__(&arg_i, &res_i, &struct_i, chr);
	while ((*ptr)[++arg_i])
	{
		if (chr[B_SLA] == '\0' && chr[QUO] == '\0' && is_quo((*ptr)[arg_i]))
			chr[QUO] = (*ptr)[arg_i];
		else if (chr[B_SLA] == '\0' && chr[QUO] == (*ptr)[arg_i])
			chr[QUO] = '\0';
		if (((*ptr)[arg_i] == '$' &&
			((*ptr)[arg_i + 1] != '\0' && (*ptr)[arg_i + 1] != chr[QUO])
			&& (chr[B_SLA] == '\0')))
			arg_i += stock_envval_and_return_index(res, (*ptr)[arg_i + 1],
				&res_i, &(string[++struct_i])) - 1;
		else
			fill_normal_with_slash_support__(res, &res_i, chr, &(*ptr)[arg_i]);
	}
	if (chr[QUO])
		res[res_i++] = chr[QUO];
	if (chr[B_SLA])
		res[res_i++] = chr[B_SLA];
	res[res_i] = '\0';
}

static bool	do_main(char **ptr, int dollar_num, t_minishell *info)
{
	char	*res;
	t_str	string[dollar_num];

	if (!(res = malloc((size_t)after_changed_len__(*ptr, info, string) + 1)))
		return (false);
	fill_in_return_str(res, ptr, string);
	ptr_free((void **)ptr);
	*ptr = res;
	return (true);
}

bool		change_env_for_here_doc(char **ptr, t_minishell *info)
{
	int		dollar_num;
	int		i;

	dollar_num = 0;
	i = -1;
	while ((*ptr)[++i])
	{
		if ((*ptr)[i] == '$')
			dollar_num++;
	}
	if (dollar_num != 0)
	{
		if (false == do_main(ptr, dollar_num, info))
			all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
		return (true);
	}
	return (false);
}
