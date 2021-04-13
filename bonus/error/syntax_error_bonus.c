/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 02:18:39 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/13 14:03:38 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../bonus_includes/minishell_bonus.h"

static ssize_t	syntax_error2(int type)
{
	ssize_t	write_rc;

	write_rc = 0;
	if (type == F_INPUT)
		write_rc = write(STDERR, SYNTAX_INPUT, 50);
	else if (type == NEWLINE)
		write_rc = write(STDERR, SYNTAX_NL, 56);
	else if (type == F_DB_SEMICOLON)
		write_rc = write(STDERR, ERR_DB_SEMICOLON, 47);
	else if (type == F_DB_PIPE)
		write_rc = write(STDERR, ERR_DB_PIPE, 47);
	else if (type == F_DB_INPUT)
		write_rc = write(STDERR, ERR_DB_INPUT, 47);
	else if (type == F_TR_INPUT)
		write_rc = write(STDERR, ERR_TR_INPUT, 48);
	else if (type == F_OUTPUT_PIPE)
		write_rc = write(STDERR, ERR_OUTPUT_PIPE, 47);
	return (write_rc);
}

bool	syntax_error(int type, t_minishell *info)
{
	ssize_t	write_rc;

	write_rc = 0;
	red_error();
	if (type == F_OUTPUT)
		write_rc = write(STDERR, SYNTAX_OP, 50);
	else if (type == F_DB_OUTPUT)
		write_rc = write(STDERR, SYNTAX_DB_OP, 51);
	else if (type == F_SEMICOLON)
		write_rc = write(STDERR, SYNTAX_SEMICOLON, 50);
	else if (type == F_PIPE)
		write_rc = write(STDERR, SYNTAX_PIPE, 50);
	write_rc = syntax_error2(type);
	if (write_rc == -1)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	g_global.exit_status = 258;
	return (false);
}
