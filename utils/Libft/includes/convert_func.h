/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_func.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 20:46:17 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/15 20:45:31 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERT_FUNC_H
# define CONVERT_FUNC_H

# include "libft.h"
# include <stdbool.h>

int				ft_atoi(const char *str);
long long		ft_atol(const char *str, bool *overflow, bool *digit_flag);
char			*ft_itoa(int n);
int				ft_stod(char *str, double *d);
int				ft_stoi(char *str, int *i);
int				ft_stov(char *s, t_p3 *p);
int				ft_tolower(int c);
int				ft_toupper(int c);
char			*skip_space(char *s);
void			str_tolower(char **s);
char			**split_by_str(char *str, char *charset);
char			**ft_split(char const *s, char c);

#endif
