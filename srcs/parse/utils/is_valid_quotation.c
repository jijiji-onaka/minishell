/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_quotation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 21:12:16 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/11 13:26:12 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// derectory 移動させる　ヘッダーファイルも移動させる
static char	return_back_slash_or_null(char chr[2], char *now)
{
	if (chr[B_SLA] == '\0' && *now == '\\')
		return ('\\');
	return ('\0');
}

bool	is_valid_command_quotations(char *command, char *first_quo)
{
	char	chr[2];
	int		arg_i;

	chr[QUO] = *first_quo;
	chr[B_SLA] = '\0';
	arg_i = -1;
	while (command[++arg_i])
	{
		if (chr[B_SLA] == '\0' && chr[QUO] == '\0' && is_quo(command[arg_i]))
			chr[QUO] = command[arg_i];
		else if (chr[B_SLA] == '\0' && chr[QUO] == command[arg_i])
			chr[QUO] = '\0';
		else if (chr[QUO] != '\'' && chr[B_SLA] == '\0'
			&& command[arg_i] == '\\')
			chr[B_SLA] = '\\';
		else if (chr[QUO] != '\'')
			chr[B_SLA] = return_back_slash_or_null(chr, command);
	}
	if (chr[QUO])
	{
		*first_quo = chr[QUO];
		return (false);
	}
	*first_quo = '\0';
	return (true);
}

int	is_valid_command_pipe(char *command)
{
	while (ft_isspace(*command))
		command++;
	if (command[0] == '|' && command[1] == '\0')
		return (FIRST_PIPE);
	while (*command)
	{
		while (*command && *command != '|')
			command++;
		if (command[0] == '|')
			if (skip_space(command + 1)[0] == '\0')
				return (LAST_PIPE);
		if (command[0] == '\0')
			return (true);
		if (command[0] == '|' && command[1] == '|' && command[2] == '|')
			return (true);
		command++;
	}
	return (true);
}

int	is_valid_command_slash(char *command)
{
	if (command[0] == '\0')
		return (true);
	if (command[ft_strlen(command) - 1] == '\\')
		return (false);
	return (true);
}
