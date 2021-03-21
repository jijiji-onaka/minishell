/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:22:21 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/21 16:54:50 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_BONUS_H
# define PARSE_BONUS_H

# include "struct_etc_bonus.h"
# include "standard_lib_bonus.h"

bool		free_syntax_error(int type, char ***cmd_grp, t_minishell *info);
bool		check_format_of_command(char ***grp, t_minishell *info);
bool		cmdlst_add_back(t_minishell *info,
					char **command, int type, int fd);
int			binary_search(char *cmd);
bool		change_env_and_quo_and_slash(char **ptr, t_minishell *info);
bool		change_only_env(char **ptr, t_minishell *info);
bool		change_astarisk(char **ptr, t_minishell *info, int i);
bool		pattern_match(char *s1, char *s2);
t_wild_lst	*get_matched_files(t_wild_lst **lst,
					char *current_dir, int depth, char *asta);
t_wild_lst	*merge_lst_sort(t_wild_lst *lst);
t_wild_lst	*make_wildlst(char *value,
					t_wild_lst *next, t_wild_lst *qnext);
int			after_changed_len(char *ptr, t_minishell *info, t_str *string);
int			after_changed_len_(char *ptr, t_minishell *info,
				t_str *string);
int			envval_len_and_return_index(char *ptr, int *len,
					t_envlst *env, t_str *string);
bool		is_quo(int c);
bool		is_redir(int c);
void		preparation__(int *num1, int *num2, int *num3, char chr[2]);
void		fill_normal_with_slash_support(char *res, int *j, char chr[2],
				char *now);
void		fill_normal_with_slash_support_(char *res, int *j, char chr[2],
				char *now);
bool		is_command_exit(char *cmd);
bool		is_quo(int c);
bool		is_separator(char *str, int *flag);
bool		is_except_separator(char *str, int quo);
bool		is_valid_quotations(char **command, char *first_quo);
void		rm_quot_and_replace_env_in_split(char **split,
				t_minishell *info);
char		**rm_spaces_in_2d_array(char **arr, t_minishell *info);
char		**split_each_parts(char *str);
char		**split_each_arg(char *str);
char		**final_split(char const *s, char c);
bool		parse_command(t_minishell *info, char *command);

#endif
