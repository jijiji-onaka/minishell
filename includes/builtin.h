/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 16:25:10 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 16:56:37 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "struct_etc.h"
# include "standard_lib.h"

void		exec_bin(t_minishell_info *info, char **args);
void		exec_cd(t_minishell_info *info, t_cmdlst *cmd);
void		exec_echo(t_minishell_info *info, t_cmdlst *cmd);
void		exec_env(t_minishell_info *info, char *arg);
void		exec_exit(t_minishell_info *info);
void		exec_export(t_minishell_info *info, char **args);
void		exec_pwd(t_minishell_info *info);
void		exec_unset(t_minishell_info *info, char **args);
void		error_mandatory(char *err_message, int num, t_minishell_info *info);
bool		is_symbolic_dir(t_minishell_info *info, char *dir_name);
char		*search_env(char *str, int num, t_envlst *env_lst);
void		trace_symbolic_src(t_minishell_info *info, char *dir_name);
void		update_env_lst(t_envlst **env, char *env_name, char *env_value,
							t_minishell_info *info);

#endif
