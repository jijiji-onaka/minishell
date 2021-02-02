/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 04:06:27 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 17:30:06 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	devide_semicolon_and_redirect(int type, char ***split,
						t_minishell_info *info)
{
	ptr_2d_free((void ***)split, 1);
	add_back_command_lst(info, NULL, SEMICOLON);
	if (type == SEMI_OUTPUT)
		add_back_command_lst(info, NULL, OUTPUT);
	else if (type == SEMI_DB_OUTPUT)
		add_back_command_lst(info, NULL, DB_OUTPUT);
	else if (type == SEMI_INPUT)
		add_back_command_lst(info, NULL, DB_INPUT);
}

/*
** 入力された文字列から各コマンドをparseする関数
*/

static void	parsing(t_minishell_info *info, char *command)
{
	int			type;
	char		**split;
	const char	*base[CMD_NUM] = {"\0", "2>", "2>>", ";", ";<", ";>", ";>>",
	"<", ">", ">>", ">|", "cd", "echo", "env", "export", "pwd", "unset", "|"};
	// ">|"の扱いどうするか
	if (!(split = split_and_switch_env_value(command, ' ', info->env)))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	if (split[0] == NULL)
		return ;
	// 先にseparatorだけでバイナリーサーチしても良い
	// if (split[0][0] == 'e' && split[0][1] == 'x' && split[0][2] == 'i'
	// 	&& split[0][3] == 't' && split[0][4] == '\0')
	if (is_command_exit(split[0]) == true)
		return (add_back_command_lst(info, split, EXIT));
	type = str_bsearch(split[0], base, CMD_NUM, strcmp_regardless_of_case);
	if (type == SEMI_OUTPUT || type == SEMI_DB_OUTPUT ||
				type == SEMI_INPUT)
		return (devide_semicolon_and_redirect(type, &split, info));
	else if (type == NOT_CMD)
			return (add_back_command_lst(info, split, BIN));
	add_back_command_lst(info, split, type);
}

/*
** parsing関数でparseするためにwhileを回す関数(envpは構造体に入れると思う)
** commandもinfo->commandもmalloc済
*/

bool		parse_command(t_minishell_info *info, char *command)
{
	char	**cmd_grp;
	char	*tmp;
	int		i;

	tmp = skip_space(command);
	if (!(cmd_grp = split_each_parts(tmp)))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	cmd_grp = rm_spaces_in_2d_array(cmd_grp, info);
	ptr_free((void **)&(command));
	if (check_format_of_command(&cmd_grp, info) == false)
		return (false);
	i = -1;
	while (cmd_grp[++i])
	{
		printf("[%d] : [%s]\n", i, cmd_grp[i]);
		parsing(info, cmd_grp[i]);
	}
	ptr_2d_free((void ***)&cmd_grp, i);
	return (true);
}
