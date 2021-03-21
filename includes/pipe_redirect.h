/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redirect.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 21:55:45 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/21 01:52:10 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_REDIRECT_H
# define PIPE_REDIRECT_H

# include "struct_etc.h"
# include "standard_lib.h"

void		close_pipe_fd(int pipefd[2], t_minishell *info);
void		connect_std_in_out_and_pipe(int pipefd[2], int i_o,
				t_minishell *info);
bool		err_no_such_file_or_directory(char *filename,
				t_minishell *info);
bool		err_ambiguous_redirect(char **filename, t_minishell *info);
void		free_alloc_ptr_in_cmd_lst(t_cmdlst **cmd_lst);
char		**get_arg_behind_redir_for_first(t_cmdlst *cmd,
				t_minishell *info);
void		get_arg_behind_redir(t_cmdlst *cmd, t_minishell *info);
void		mix_input_and_output(int fd[3], t_cmdlst *begin,
				t_minishell *info);
void		mix_input_and_stderr_output(int fd[3], t_cmdlst *begin,
				t_minishell *info);
int			open_files_and_stock_fd(int (*fd)[2],
				t_cmdlst **cmd_lst, t_minishell *info);
void		prepare_redirect_put(int (*fd)[2], int *backup,
				t_cmdlst *lst, t_minishell *info);
void		cleanup_redirect_put(int (*fd)[2], int *backup,
				t_cmdlst *lst, t_minishell *info);
void		read_from_file(int fd, t_cmdlst *begin, t_minishell *info);
t_cmdlst	*skip_cmdlst(t_cmdlst **cmd_lst, size_t how_many, bool flag);
void		write_to_file(int fd, int std, t_cmdlst *begin,
					t_minishell *info);
t_cmdlst	*my_pipe(t_minishell *info, t_cmdlst **cmd_lst, int fd);
bool		is_now_middle_pipe(t_cmdlst *lst);
void		skip_command(t_cmdlst **cmd_lst);
t_cmdlst	*get_next_command(t_cmdlst *lst);
t_cmdlst	*my_redirect(t_minishell *info, t_cmdlst **cmd_lst);
t_cmdlst	*redir_first(t_minishell *info, t_cmdlst **cmd_lst);

#endif
