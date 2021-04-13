/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 16:25:10 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/13 13:51:37 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_BONUS_H
# define BUILTIN_BONUS_H

# include "struct_etc_bonus.h"
# include "standard_lib_bonus.h"

/*
**  CD
*/
void		exec_cd(t_minishell *info, t_cmdlst *cmd);
void		go_path(t_minishell *info, char **dir);
bool		is_cdpath(t_minishell *info, char **dir);
void		go_to_home(t_minishell *info);
void		not_set_home_path(t_minishell *info);
bool		go_cwd(t_minishell *info, char *dir, char *real_dir);
void		go_oldpwd(t_minishell *info);
void		set_oldpwd(t_minishell *info, char *oldpwd);
bool		is_symbolic_dir(t_minishell *info, char *dir_name);
void		go_to_upper_dir(char *now, t_minishell *info);
void		connect_path(char **src, char *dst, t_minishell *info);
bool		not_found_cwd(t_minishell *info, char *arg_dir, char ***ptr);
/*
** BIN
*/
void		exec_bin(t_minishell *info, t_cmdlst *cmd);
char		**get_environ(t_envlst *lst, t_minishell *info);
char		*check_executable_file_in_bin_dir(char *path, char **command,
				t_minishell *info);
bool		no_exe_file_in_bin_dir(char *file, t_minishell *info);
void		not_builtin(char *command,
				t_minishell *info, bool path_flag);
/*
** ECHO
*/
void		exec_echo(t_minishell *info, t_cmdlst *cmd);
/*
** ENV
*/
void		exec_env(t_minishell *info, t_cmdlst *cmd);
/*
** EXIT
*/
void		exec_exit(t_minishell *info, t_cmdlst *cmd);
bool		set_numeric_flag(char *arg);
/*
** EXPORT
*/
void		exec_export(t_minishell *info, t_cmdlst *cmd);
bool		is_valid_env_name(char **env_name, char *arg, t_minishell *info);
void		display_sorted_env(t_minishell *info);
void		*destroy_queue(t_envlst **qhead);
t_envlst	*merge_lst_sort(t_envlst *lst);
void		joint_env_value(t_string *key, t_string *value, t_minishell *info);
void		update_env_lst(t_envlst **env, t_string key, t_string value,
				t_minishell *info);
void		update_env_value(t_envlst **env, char *key, char *value,
				t_minishell *info);
/*
** PWD
*/
void		exec_pwd(t_minishell *info, t_cmdlst *cmd);
/*
** unset
*/
void		exec_unset(t_minishell *info, t_cmdlst *cmd);
void		remove_env_lst_if(t_envlst **env, char *data);

#endif
