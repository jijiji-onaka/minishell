/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 12:25:33 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/10 12:13:00 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static bool	check_quotation(t_string *command, t_minishell *info)
{
	char	quo;

	quo = '\0';
	if (is_valid_command_quotations(command->str, &quo) == false)
		if (read_quotation(quo, command, info) == false)
			return (false);
	return (true);
}

static bool	check_pipe(t_string *command, t_minishell *info)
{
	int	pipe_ret;

	pipe_ret = is_valid_command_pipe(command->str);
	if (pipe_ret == FIRST_PIPE)
		return (syntax_error(F_PIPE, info));
	else if (pipe_ret == LAST_PIPE)
		if (read_add_command(command, is_valid_command_pipe, info) == false)
			return (false);
	return (true);
}

static bool	check_slash(t_string *command, t_minishell *info)
{
	int	pipe_ret;

	pipe_ret = is_valid_command_slash(command->str);
	if (is_valid_command_slash(command->str) == false)
		if (read_add_command(command, is_valid_command_slash, info) == false)
			return (false);
	return (true);
}

void	*check_format(t_string *command, t_minishell *info)
{
	int	check;

	check = 0;
	while (check != 6)
	{
		if (check_quotation(command, info) == false)
			return (NULL);
		check++;
		if (check == 6)
			break ;
		if (check_pipe(command, info) == false)
			return (NULL);
		check++;
		if (check == 6)
			break ;
		if (check_slash(command, info) == false)
			return (NULL);
		check++;
		if (check == 6)
			break ;
	}
	return ((void *)1);
}
