/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_function_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 02:27:12 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/13 13:52:59 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SAFE_FUNCTION_BONUS_H
# define SAFE_FUNCTION_BONUS_H

# include "struct_etc_bonus.h"
# include "standard_lib_bonus.h"
# include "minishell_bonus.h"

void		putstr_fd(char *str, int fd, t_err err, t_minishell *info);
void		putchar_fd(char chr, int fd, t_err err, t_minishell *info);
ssize_t		safe_read(char buf[4], char **ptr, t_minishell *info);
void		*safe_malloc(size_t len, t_err err, t_minishell *info);
bool		safe_opendir(DIR **dp, char *dir, t_minishell *info);
bool		safe_readdir(struct dirent **dirp, DIR *dp, t_minishell *info);
void		safe_closedir(DIR **dp, t_minishell *info);
bool		safe_chdir(char *dir, char **split, t_minishell *info);

#endif
