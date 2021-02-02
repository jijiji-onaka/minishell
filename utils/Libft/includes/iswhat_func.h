/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iswhat_func.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 20:46:35 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/22 02:15:28 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ISWHAT_FUNC_H
# define ISWHAT_FUNC_H

# include <stdbool.h>

bool		ft_isalnum(int c);
bool		ft_isalpha(int c);
bool		ft_isascii(int c);
bool		ft_isdigit(int c);
bool		ft_isprint(int c);
bool		ft_isspace(int c);
bool		is_float(char *s);

#endif
