/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_stdin_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:42:21 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/21 20:58:10 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_STDIN_BONUS_H
# define READ_STDIN_BONUS_H

# include "struct_etc_bonus.h"
# include "standard_lib_bonus.h"

void	ctrl_d_exit(char **ptr, t_minishell *info);
void	ctrl_d_rm(char **ptr, t_minishell *info);
void	rm_chr_in_str(char **str, char chr);
void	rm_chrs_in_str(char **str, char *chrs);
ssize_t	safe_read(char *buf, char **ptr, t_minishell *info);
char	*waiting_for_input(t_minishell *info);
char	*waiting_for_next_command(char ***cmd_grp, int array_size,
						t_minishell *info);
void	display_what_is_waiting_for(char quo, char **ptr1, char **ptr2,
						t_minishell *info);
int		check_more_pipe(char **inputs, t_cmd_grp *cmd_grp_info,
						t_minishell *info);
char	*reset_prompt(char **ptr1, char **ptr2);
char	*waiting_for_quotation(char first_quo, char **command, \
						t_minishell *info);

#endif
