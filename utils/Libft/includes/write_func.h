/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_func.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 20:46:47 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/10 20:38:53 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRITE_FUNC_H
# define WRITE_FUNC_H

# include "libft.h"

bool	ft_putchar_fd(char c, int fd);
bool	ft_putendl_fd(char *s, int fd);
bool	ft_putnbr_fd(int n, int fd);
bool	ft_putstr_fd(char *s, int fd);
void	red_error(void);
void	yellow_warning(void);

#endif
