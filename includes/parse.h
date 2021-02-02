/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:22:21 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 17:30:12 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "struct_etc.h"
# include "standard_lib.h"

bool	ptr_2d_free_and_syntax_error(int type, char ***cmd_grp,
			t_minishell_info *info);
bool	check_format_of_command(char ***grp, t_minishell_info *info);
bool	is_output_format_error(char ***grp, int i, t_minishell_info *info);
bool	is_pipe_format_error(char ***grp, int i, t_minishell_info *info);
bool	is_semicolon_format_error(char ***grp, int i, \
			t_minishell_info *info);
void	add_back_command_lst(t_minishell_info *info,
			char **command, int type);
int		switch_env_value(char **s, char **res, t_envlst *env_lst);
bool	is_command_exit(char *cmd);
bool	isalnum_except_next_redir(char *str);
char	**rm_spaces_in_2d_array(char **arr, t_minishell_info *info);
char	**split_and_switch_env_value(char *s, char c, t_envlst *env_lst);
char	**split_each_parts(char *str);
bool	parse_command(t_minishell_info *info, char *command);

#endif
