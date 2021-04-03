/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_stdin.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:42:21 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/03 18:26:26 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_STDIN_H
# define READ_STDIN_H

# include "struct_etc.h"
# include "standard_lib.h"

void	get_window_size(t_minishell *info);
bool	get_cursor_position(int pos[2], t_minishell *info);
void	check_key(char *buf, t_string *command, t_minishell *info);
void	trace_history_up(char *buf, t_string *command, t_minishell *info);
void	trace_history_down(char *buf, t_string *command, t_minishell *info);
void	move_up_one_line(char *buf, t_string *command, t_minishell *info);
void	move_down_one_line(char *buf, t_string *command, t_minishell *info);
void	moving(size_t len, char *move_direction, t_minishell *info);
void	move_cursor_left(char *buf, t_string *command, t_minishell *info);
void	move_cursor_right(char *buf, t_string *command, t_minishell *info);
void	move_left_directly_word_toward(char *buf, t_string *command,
								t_minishell *info);
void	move_right_directly_word_toward(char *buf, t_string *command,
								t_minishell *info);
void	delete_displayed_char(char *buf, t_string *command, t_minishell *info);
bool	delete_displayed_command(size_t len, char *left, char *clean);
void	clear_terminal(char *buf, t_string *command, t_minishell *info);
void	print_user_pushed_char(char *buf, t_string *command, t_minishell *info);
void	pushed_newline(char *buf, t_string *command, t_minishell *info);
void	do_nothing(char *buf, t_string *command, t_minishell *info);
void	go_line_beginning(char *buf, t_string *command, t_minishell *info);
void	go_line_end(char *buf, t_string *command, t_minishell *info);
void	select_target_left(char *buf, t_string *command, t_minishell *info);
void	select_target_right(char *buf, t_string *command, t_minishell *info);
void	copy(char *buf, t_string *command, t_minishell *info);
void	paste(char *buf, t_string *command, t_minishell *info);
void	cut(char *buf, t_string *command, t_minishell *info);
int		check_more_pipe(char **inputs, t_cmd_grp *cmd_grp_info,
						t_minishell *info);
void	ctrl_d_exit(char *buf, t_string *command, t_minishell *info);
void	ctrl_d_rm(char **ptr, t_minishell *info);
void	display_what_is_waiting_for(char quo, char **ptr1, char **ptr2,
						t_minishell *info);
char	*reset_prompt(char **ptr1, char **ptr2);
void	rm_chr_in_str(char **str, char chr);
ssize_t	safe_read(char buf[4], char **ptr, t_minishell *info);
char	*waiting_for_input(t_minishell *info);
char	*waiting_for_next_command(char ***cmd_grp, int array_size,
						t_minishell *info);
char	*waiting_for_quotation(char first_quo, char **command, \
						t_minishell *info);

#endif
