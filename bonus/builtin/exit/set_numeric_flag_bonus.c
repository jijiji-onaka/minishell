/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_numeric_flag_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 18:00:10 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/13 14:03:24 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bonus_includes/minishell_bonus.h"

static char	*skip(char *s)
{
	while (*s && (*s == ' ' || *s == '+' || *s == '-'))
		s++;
	return (s);
}

bool	set_numeric_flag(char *arg)
{
	bool		overflow_flag;
	bool		digit_flag;
	char		*no_space;

	overflow_flag = false;
	digit_flag = false;
	ft_atol(arg, &overflow_flag, &digit_flag);
	no_space = skip(arg);
	if (no_space[0] == '\0')
		return (false);
	if (overflow_flag || is_float(no_space) || digit_flag
		|| !ft_isdigit(no_space[0]))
		return (false);
	return (true);
}
