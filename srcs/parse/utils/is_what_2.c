/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_what_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 18:27:21 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/12 20:03:43 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static bool	check_fd_redirect(char **str)
{
	char	*begin;

	begin = *str;
	if (!ft_isdigit(**str))
		return (false);
	(*str)++;
	while (*str && ft_isdigit(**str))
		(*str)++;
	if (**str == '>' || **str == '<')
		return (true);
	*str = begin;
	return (false);
}

bool		is_except_separator(char *str, int quo)
{
	if (quo > 0 && *str != quo)
		return (1);
	if (quo != -1 && quo == *str)
		return (1);
	return (!((*str == '|' || *str == '>'
	|| *str == '<'
	|| *str == ';'
	|| check_fd_redirect(&str))));
}

bool		is_separator(char *str, int *flag)
{
	bool	f;
	char	*tmp;

	tmp = str;
	f = check_fd_redirect(&str);
	if (f)
		return (1);
	if (flag == NULL)
		;
	else if (*str != '<' && *flag == 2)
		return (*flag = 0);
	else if (*flag == 3)
		return (false);
	else if (*str == *(str + 1) || (*str == '>' && *(str + 1) == '|'))
		return (*flag += 1);
	else if (*str != *(str + 1))
		return (*flag = 3);
	else if (tmp == str)
		*flag += 1;
	return (((*str == '|' || *str == '>' || *str == '<' || *str == ';' || f)));
}
