/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_quotation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 21:12:16 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/21 14:04:44 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool	is_valid_quotations(char **command, char *first_quo)
{
	char	chr[2];
	int		arg_i;

	chr[QUO] = *first_quo;
	chr[B_SLA] = '\0';
	arg_i = -1;
	while ((*command)[++arg_i])
	{
		if (chr[B_SLA] == '\0' && chr[QUO] == '\0' && is_quo((*command)[arg_i]))
			chr[QUO] = (*command)[arg_i];
		else if (chr[B_SLA] == '\0' && chr[QUO] == (*command)[arg_i])
			chr[QUO] = '\0';
		else if (chr[QUO] != '\'' && chr[B_SLA] == '\0'
					&& (*command)[arg_i] == '\\')
			chr[B_SLA] = '\\';
		else if (chr[QUO] != '\'')
			chr[B_SLA] = ((!chr[B_SLA] && (*command)[arg_i] == '\\') ?
						'\\' : '\0');
	}
	if (chr[QUO])
	{
		*first_quo = chr[QUO];
		return (false);
	}
	return (true);
}
