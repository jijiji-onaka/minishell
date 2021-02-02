/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redirect.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 21:55:45 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 17:48:13 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_REDIRECT_H
# define  PIPE_REDIRECT_H

# include "struct_etc.h"
# include "standard_lib.h"

void		close_pipe_fd(int pipefd[2], t_minishell_info *info);
void		connect_std_in_out_and_pipe(int pipefd[2], int i_o,
				t_minishell_info *info);
bool		err_no_such_file_or_directory(char *filename, t_minishell_info *info);
void		free_alloc_ptr_in_cmd_lst(t_cmdlst **cmd_lst);
void		mix_input_and_output(int fd[3], t_cmdlst *begin,
				t_minishell_info *info);
void		mix_input_and_stderr_output(int fd[3], t_cmdlst *begin,
				t_minishell_info *info);
int			open_files_and_stock_fd(int fd[3], int type,
				t_cmdlst **cmd_lst, t_minishell_info *info);
void		just_open_file(t_minishell_info *info, t_cmdlst *cmd);
void		read_from_file(int fd, t_cmdlst *begin, t_minishell_info *info);
t_cmdlst	*skip_lst_and_free(t_cmdlst **cmd_lst, int how_many);
void		write_to_file(int fd, int std, t_cmdlst *begin,
					t_minishell_info *info);
t_cmdlst	*pipe_sep(t_minishell_info *info, t_cmdlst **cmd_lst);
t_cmdlst	*redirect_sep(t_minishell_info *info, t_cmdlst **cmd_lst);

#endif
