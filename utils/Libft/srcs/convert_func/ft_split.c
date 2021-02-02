/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 11:43:10 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/04 03:18:40 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/convert_func.h"

static size_t	word_count(char const *s, char c)
{
	size_t		cnt;

	cnt = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s && *s != c)
		{
			cnt++;
			while (*s && *s != c)
				s++;
		}
	}
	return (cnt);
}

static size_t	word_length(char const *s, char c)
{
	size_t		i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static char		**insert_word(char const *s, char c, size_t wc, char **res)
{
	size_t		i;
	size_t		j;
	size_t		len;

	i = 0;
	while (i < wc)
	{
		while (*s == c)
			s++;
		len = word_length(s, c);
		if (!(res[i] = malloc(sizeof(char) * (len + 1))))
			return (ptr_2d_free((void***)&res, i));
		j = 0;
		while (j < len)
		{
			res[i][j++] = *s++;
		}
		res[i][j] = '\0';
		i++;
	}
	res[i] = NULL;
	return (res);
}

char			**ft_split(char const *s, char c)
{
	char		**res;
	size_t		wc;

	if (!s)
		return (NULL);
	wc = word_count(s, c);
	if (wc == 0)
	{
		if (!(res = malloc(sizeof(char *) * 1)))
			return (NULL);
		res[0] = NULL;
		return (res);
	}
	if (!(res = malloc(sizeof(char *) * (wc + 1))))
		return (NULL);
	res = insert_word(s, c, wc, res);
	return (res);
}
