/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 02:18:39 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 17:08:42 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static ssize_t	syntax_error2(int type)
{
	ssize_t	write_rc;

	write_rc = 0;
	if (type == INPUT)
		write_rc = write(2, SYNTAX_INPUT, 50);
	else if (type == SYNTAX_EOL_NUM)
		write_rc = write(2, SYNTAX_EOL, 48);
	else if (type == NEWLINE)
		write_rc = write(2, SYNTAX_NL, 56);
	else if (type == NOT_CMD)
		write_rc = write(2, ERR_MANDATORY, 44);
	else if (type == DB_SEMICOLON)
		write_rc = write(2, ERR_DB_SEMICOLON, 47);
	else if (type == DB_PIPE)
		write_rc = write(2, ERR_DB_PIPE, 47);
	else if (type == OUTPUT_PIPE)
		write_rc = write(2, ERR_OUTPUT_PIPE, 47);
	else if (type == DB_INPUT)
		write_rc = write(2, ERR_DB_INPUT, 47);
	else if (type == TR_INPUT)
		write_rc = write(2, ERR_TR_INPUT, 48);
	return (write_rc);
}

bool			syntax_error(int type, t_minishell_info *info)
{
	ssize_t	write_rc;

	write_rc = 0;
	red_error();
	if (type == OUTPUT)
		write_rc = write(2, SYNTAX_OP, 50);
	else if (type == DB_OUTPUT)
		write_rc = write(2, SYNTAX_DB_OP, 51);
	else if (type == SEMICOLON)
		write_rc = write(2, SYNTAX_SEMICOLON, 50);
	else if (type == PIPE)
		write_rc = write(2, SYNTAX_PIPE, 50);
	write_rc = syntax_error2(type);
	if (write_rc == -1)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	g_signal.exit_status = 258;
	return (false);
}
