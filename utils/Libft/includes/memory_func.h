/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_func.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 20:46:41 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/11 21:29:17 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_FUNC_H
# define MEMORY_FUNC_H

# include "libft.h"

void	ft_bzero(void *s, size_t n);
void	*ft_memccpy(void *dst, const void *src, int c, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_calloc(size_t count, size_t size);

#endif
