/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_stdin.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:42:21 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/13 12:28:07 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_STDIN_H
# define READ_STDIN_H

# include "struct_etc.h"
# include "standard_lib.h"
# include "minishell.h"

struct winsize	get_window_size(t_minishell *info);
bool			get_cursor_position(int pos[2], t_minishell *info);
void			dup_pos(int dst[2], int src[2]);
bool			equal_pos(int cmp_1[2], int cmp_2[2]);
void			handle_forward_cursor_pos(int pos[2],
					int start_pos[2], int end_pos[2], t_minishell *info);
bool			is_right_edge(struct winsize winsize, int pos[2]);
bool			is_win_bottom_edge(struct winsize winsize, int pos[2]);
bool			is_win_bottom_right_edge(struct winsize winsize, int pos[2]);
// void			handle_back_cursor_pos(int pos[2], int window_max_x);
void			handle_back_cursor_pos(t_string *command, int pos[2],
					t_minishell *info, int window_max_x);
void			display_command(t_string *command, t_minishell *info);
void			scroll_window(t_minishell *info,
					struct winsize winsize, char now_chr);
int				get_command_len_from_pos(int pos_end[2], int pos_start[2],
					t_minishell *info);
int				get_from_nl_to_nl(t_string *command, t_cursor cursor, int pos[2]);
int				get_now_index(t_minishell *info, t_string *command);
int				get_key_id(char *buf, t_string *command, t_minishell *info);
void			check_key(char *buf, t_string *command, t_minishell *info);
void			check_key_multiple_line(char multiple_line_char, char *buf,
					t_string *cmd, t_minishell *info);
void			trace_history_up(char *buf, t_string *command,
					t_minishell *info);
void			trace_history_down(char *buf, t_string *command,
					t_minishell *info);
void			move_up_one_line(char *buf, t_string *command,
					t_minishell *info);
void			move_down_one_line(char *buf, t_string *command,
					t_minishell *info);
void			move_specified_position(int pos_y, int pos_x, t_err err,
					t_minishell *info);
void			move_cursor_left(char *buf, t_string *command,
					t_minishell *info);
void			move_cursor_right(char *buf, t_string *command,
					t_minishell *info);
void			move_word_directly_to_left(char *buf, t_string *command,
					t_minishell *info);
void			move_word_directly_to_right(char *buf, t_string *command,
					t_minishell *info);
void			delete_displayed_char(char *buf, t_string *command,
					t_minishell *info);
void			delete_displayed_command(t_err err, t_string *command,
					t_minishell *info);
void			clear_terminal(char *buf, t_string *command, t_minishell *info);
void			print_user_pushed_char(char *buf, t_string *command,
					t_minishell *info);
void			pushed_newline(char *buf, t_string *command, t_minishell *info);
void			do_nothing(char *buf, t_string *command, t_minishell *info);
void			go_command_beginning(char *buf, t_string *command,
					t_minishell *info);
void			go_command_end(char *buf, t_string *command, t_minishell *info);
void			select_target_left(char *buf, t_string *command,
					t_minishell *info);
void			select_target_right(char *buf, t_string *command,
					t_minishell *info);
void			copy_command(char *buf, t_string *command, t_minishell *info);
void			paste_selected_str(char *buf, t_string *command,
					t_minishell *info);
void			cut_command(char *buf, t_string *command, t_minishell *info);
void			ctrl_d_exit(char *buf, t_string *command, t_minishell *info);
void			ctrl_d_put_error(char *buf, t_string *command,
					t_minishell *info);
int				check_more_pipe(char **inputs, t_cmd_grp *cmd_grp_info,
					t_minishell *info);
void			*check_format(t_string *command, t_minishell *info);
void			display_what_is_waiting_for(char chr, char **ptr1, char **ptr2,
					t_minishell *info);
char			*reset_prompt(char **ptr1, char **ptr2);
char			*read_command(t_minishell *info);
char			*read_add_command(t_string *command,
					int (*is_valid)(char *), t_minishell *info);
char			*read_quotation(char first_quo, t_string *commnad, \
					t_minishell *info);

#endif
