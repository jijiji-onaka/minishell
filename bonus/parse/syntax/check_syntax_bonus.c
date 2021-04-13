/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 00:05:31 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/09 11:05:56 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bonus_includes/minishell_bonus.h"

static bool	free_syntax_error(int type, char ***cmd_grp, t_minishell *info)
{
	ptr_2d_free((void ***)cmd_grp, -1);
	return (syntax_error(type, info));
	return (syntax_error(type, info));
}

static bool	pipe_end(t_minishell *info, int i, char ***grp, int type)
{
	if (type == F_DB_PIPE)
		return (free_syntax_error(F_DB_PIPE, grp, info));
	if (i == 1)
		return (free_syntax_error(F_PIPE, grp, info));
	if (*grp == NULL)
		return (false);
	return (true);
}

static bool	is_redir_for_format(int type)
{
	return (type == F_INPUT || type == F_DB_INPUT
		|| type == F_OUTPUT || type == F_DB_OUTPUT);
}

/*
** !(before >= 1 && before <= 12) -> normal command
** (before >= 1 && before <= 12) -> separator
*/

static bool	display_format_error_message(int before, int now,
					char ***grp, t_minishell *info)
{
	if (before == -1 && (now == F_SEMICOLON || now == F_PIPE
			|| now == F_DB_AND || now == F_AND || now == F_DB_PIPE))
		return (free_syntax_error(now, grp, info));
	else if ((before == -1 || before == F_SEMICOLON || before == F_PIPE
			|| before == F_DB_PIPE || before == F_AND)
		&& (now == F_CMD_NUM || is_redir_for_format(now)))
		return (true);
	else if (now == F_CMD_NUM && before == F_TR_INPUT)
		return (free_syntax_error(F_TR_INPUT, grp, info));
	else if ((now == F_PIPE || now == F_DB_PIPE) && before == F_DB_PIPE)
		return (free_syntax_error(now, grp, info));
	else if (now == F_TR_INPUT)
		return (true);
	else if (now == F_AND || now == F_DB_SEMICOLON || now == F_OUTPUT_PIPE)
		return (free_syntax_error(now, grp, info));
	if ((now == F_SEMICOLON && !(before >= 1 && before <= 12))
		|| now == F_CMD_NUM || !(before >= 1 && before <= 12))
		return (true);
	else if (now == F_DB_INPUT && before == F_DB_INPUT)
		return (free_syntax_error(F_INPUT, grp, info));
	else if ((now == F_PIPE || now == F_DB_PIPE) && before == F_DB_PIPE)
		return (free_syntax_error(now, grp, info));
	return (free_syntax_error(now, grp, info));
}

bool	check_syntax(char ***grp, t_minishell *info)
{
	int			i[2];
	int			now_type;
	int			before_type;
	const char	*base[F_CMD_NUM] = {"\0", "&", "&&", ";", ";;", "<", "<<",
	"<<<", ">", ">>", ">|", "|", "||"};

	i[0] = -1;
	before_type = -1;
	while ((*grp)[++i[0]])
	{
		i[1] = 0;
		while ((*grp)[i[0]][i[1]] && ft_isdigit((*grp)[i[0]][i[1]]))
			i[1]++;
		now_type = str_bsearch((*grp)[i[0]] + i[1], base, F_CMD_NUM, ft_strcmp);
		if (!display_format_error_message(before_type, now_type, grp, info))
			return (false);
		before_type = now_type;
	}
	if (is_redir_for_format(now_type))
		return (free_syntax_error(NEWLINE, grp, info));
	info->cmd_lst_num = i[0];
	if (now_type == F_PIPE || now_type == F_DB_PIPE)
		return (pipe_end(info, i[0], grp, now_type));
	return (true);
}
