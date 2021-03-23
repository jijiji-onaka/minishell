/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 16:25:10 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/21 21:02:13 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "struct_etc.h"
# include "standard_lib.h"

void		exec_bin(t_minishell *info, t_cmdlst *cmd);
void		exec_cd(t_minishell *info, t_cmdlst *cmd);
void		exec_echo(t_minishell *info, t_cmdlst *cmd);
void		exec_env(t_minishell *info, t_cmdlst *cmd);
void		exec_exit(t_minishell *info, t_cmdlst *cmd);
void		exec_export(t_minishell *info, t_cmdlst *cmd);
void		exec_pwd(t_minishell *info, t_cmdlst *cmd);
void		exec_unset(t_minishell *info, t_cmdlst *cmd);

void		display_sorted_env(t_minishell *info);
void		*destroy_queue(t_envlst **qhead);
t_envlst	*merge_lst_sort(t_envlst *lst);
void		error_mandatory(char *err_message, int num, t_minishell *info);
bool		is_symbolic_dir(t_minishell *info, char *dir_name);
void		go_to_upper_dir(char *now, t_minishell *info);
void		update_current_dir(t_minishell *info, char *dir);
bool		not_found_cwd(t_minishell *info, char *arg_dir, char ***ptr);
char		*relative_path(char *now, char *dir, t_minishell *info);
char		*absolute_path(char *now, char *dir, t_minishell *info);
char		*make_env_name(char *arg, int *i, t_minishell *info);
char		*make_env_value(char *arg, t_minishell *info, char **ptr);
char		*add_env_value(char *arg, t_minishell *info, char **ptr);
void		when_only_env_name(char *arg, t_minishell *info);
bool		safe_chdir(char *dir, char **split, t_minishell *info);
char		*search_env(char *str, int num, t_envlst *env_lst, bool *flag);
void		go_to_home(t_minishell *info);
void		not_set_home_path(t_minishell *info);
bool		go_to_cwd(t_minishell *info, char *dir, char *real_dir);
void		go_to_path(t_minishell *info, char **dir,
					bool option_p_flag);
void		go_to_oldpwd(t_minishell *info);
void		set_oldpwd(t_minishell *info, char *oldpwd);
void		remove_env_lst_if(t_envlst **env, char *data);
bool		set_numeric_flag(char *arg);
char		*skip(char *s);
void		two_free(void **one, void **two);
void		update_env_lst(t_envlst **env, char *env_name, char *env_value,
							t_minishell *info);
bool		is_parameter(char c);
char		**get_environ(t_envlst *lst, t_minishell *info);
int			check_bash_standard_commands(t_minishell *info, char **command
				, bool *path_flag);
char		*check_executable_file_in_bin_dir(char *path, char **command,
				t_minishell *info);
bool		no_exe_file_in_bin_dir(char *file, t_minishell *info);
void		not_builtin(char *command, t_minishell *info
			, bool path_flag);

#endif
