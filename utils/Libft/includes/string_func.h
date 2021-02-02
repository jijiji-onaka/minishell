/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_func.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 20:46:45 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/23 02:43:05 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_FUNC_H
# define STRING_FUNC_H

# include "libft.h"

typedef struct	s_index
{
	size_t		begin;
	size_t		end;
	size_t		mid;
}				t_index;

int				check_strtail(char *s, char *tail);
char			*ft_str3join(char *s1, char *s2, char *s3);
char			*ft_strchr(const char *s, int c);
int				ft_strcmp(char *p1, char *p2);
char			*ft_strdup(const char *s1);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strjoinch(char const *s, char c);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnstr(const char *haystack, \
					const char *needle, size_t len);
char			*ft_strrchr(const char *s, int c);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*strjoin_num(char *s, long long num);
char			*re_strjoinch(char **s, char c);
char			*re_strdup(char **s1, char *s2);
char			*re_strjoin(char **freed, char *s1, char *s2);
int				strcmp_regardless_of_case(char *p1, char *p2);
char			*numjoin_str(char *s, long long num);

#endif
