/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_output_format_error.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 03:15:08 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 17:25:10 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static bool	is_output_format_error4(char ***grp, int i, t_minishell_info *info)
{
	if ((*grp)[i + 1][0] == '|')
		return (ptr_2d_free_and_syntax_error(PIPE, grp, info));
	else if ((*grp)[i + 1][0] == ';' && (*grp)[i + 1][1] == ';')
		return (ptr_2d_free_and_syntax_error(DB_SEMICOLON, grp, info));
	else if ((*grp)[i + 1][0] == ';')
		return (ptr_2d_free_and_syntax_error(SEMICOLON, grp, info));
	else if ((*grp)[i + 1][0] == '<' && (*grp)[i + 1][1] == '<' &&
					(*grp)[i + 1][2] == '<')
		return (ptr_2d_free_and_syntax_error(TR_INPUT, grp, info));
	else if ((*grp)[i + 1][0] == '<' && (*grp)[i + 1][1] == '<')
		return (ptr_2d_free_and_syntax_error(DB_INPUT, grp, info));
	else if ((*grp)[i + 1][0] == '<')
		return (ptr_2d_free_and_syntax_error(INPUT, grp, info));
	return (true);
}

static bool	is_output_format_error3(char ***grp, int i, t_minishell_info *info)
{
	if ((*grp)[i][1] == '>' && (*grp)[i][2] == '|')
		return (ptr_2d_free_and_syntax_error(PIPE, grp, info));
	if ((*grp)[i][1] == '|' && (*grp)[i][2] == '|' && (*grp)[i][3] == '|')
		return (ptr_2d_free_and_syntax_error(DB_PIPE, grp, info));
	else if ((*grp)[i][1] == '|' && (*grp)[i][2] == '|')
		return (ptr_2d_free_and_syntax_error(PIPE, grp, info));
	else if ((*grp)[i][1] == '|')
		return (ptr_2d_free_and_syntax_error(OUTPUT_PIPE, grp, info));
	else if ((*grp)[i][1] == '<' && (*grp)[i][2] == '<' && (*grp)[i][3] == '<')
		return (ptr_2d_free_and_syntax_error(TR_INPUT, grp, info));
	else if ((*grp)[i][1] == '<' && (*grp)[i][2] == '<')
		return (ptr_2d_free_and_syntax_error(DB_INPUT, grp, info));
	else if ((*grp)[i][1] == '<')
		return (ptr_2d_free_and_syntax_error(INPUT, grp, info));
	else if (!(*grp)[i + 1])
		return (ptr_2d_free_and_syntax_error(NEWLINE, grp, info));
	else if ((*grp)[i + 1][0] == '>' && (*grp)[i + 1][1] == '>')
		return (ptr_2d_free_and_syntax_error(DB_OUTPUT, grp, info));
	else if ((*grp)[i + 1][0] == '>')
		return (ptr_2d_free_and_syntax_error(OUTPUT, grp, info));
	else if ((*grp)[i + 1][0] == '|' && (*grp)[i + 1][1] == '|')
		return (ptr_2d_free_and_syntax_error(DB_PIPE, grp, info));
	return (true);
}

static bool	is_output_format_error2(char ***grp, int i, t_minishell_info *info)
{
	if ((*grp)[i][1] == '>' && (*grp)[i][2] == '>' && (*grp)[i][3] == '>')
		return (ptr_2d_free_and_syntax_error(DB_OUTPUT, grp, info));
	else if ((*grp)[i][1] == '>' && (*grp)[i][2] == '>' && (*grp)[i][3] == '|')
		return (ptr_2d_free_and_syntax_error(OUTPUT_PIPE, grp, info));
	else if ((*grp)[i][1] == '>' && (*grp)[i][2] == '>')
		return (ptr_2d_free_and_syntax_error(OUTPUT, grp, info));
	else if ((*grp)[i][1] == '>' && (*grp)[i][2] == ';' && (*grp)[i][3] == ';')
		return (ptr_2d_free_and_syntax_error(DB_SEMICOLON, grp, info));
	else if ((*grp)[i][1] == '>' && (*grp)[i][2] == ';')
		return (ptr_2d_free_and_syntax_error(SEMICOLON, grp, info));
	else if ((*grp)[i][1] == '>' && (*grp)[i][2] == '<' && (*grp)[i][3] == '<'
		&& (*grp)[i][4] == '<')
		return (ptr_2d_free_and_syntax_error(TR_INPUT, grp, info));
	else if ((*grp)[i][1] == '>' && (*grp)[i][2] == '<' && (*grp)[i][3] == '<')
		return (ptr_2d_free_and_syntax_error(DB_INPUT, grp, info));
	else if ((*grp)[i][1] == '>' && (*grp)[i][2] == '<')
		return (ptr_2d_free_and_syntax_error(INPUT, grp, info));
	else if ((*grp)[i][1] == ';' && (*grp)[i][2] == ';')
		return (ptr_2d_free_and_syntax_error(DB_SEMICOLON, grp, info));
	else if ((*grp)[i][1] == ';')
		return (ptr_2d_free_and_syntax_error(SEMICOLON, grp, info));
	else if ((*grp)[i][1] == '>' && (*grp)[i][2] == '|' && (*grp)[i][3] == '|')
		return (ptr_2d_free_and_syntax_error(DB_PIPE, grp, info));
	return (true);
}

bool		is_output_format_error(char ***grp, int i, t_minishell_info *info)
{
	if ((*grp)[i][0] != '>')
		return (true);
	if (is_output_format_error2(grp, i, info) == false)
		return (false);
	if (is_output_format_error3(grp, i, info) == false)
		return (false);
	if (is_output_format_error4(grp, i, info) == false)
		return (false);
	return (true);
}
