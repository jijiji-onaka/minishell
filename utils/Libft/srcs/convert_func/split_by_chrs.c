/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_chrs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 21:19:52 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/09 02:25:23 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/convert_func.h"

static size_t	count_words(char *str, char *charset)
{
	size_t		word_count;

	word_count = 0;
	while (*str)
	{
		while (*str && ft_strchr(charset, *str))
			str++;
		if (*str && !ft_strchr(charset, *str))
		{
			word_count++;
			while (*str && !ft_strchr(charset, *str))
				str++;
		}
	}
	return (word_count);
}

static char	*insert_word(char *str, char *cset)
{
	char		*word;
	size_t		i;

	i = 0;
	while (str[i] && !ft_strchr(cset, str[i]))
		i++;
	word = malloc(sizeof(char) * (i + 1));
	if (word == NULL)
		return (NULL);
	i = 0;
	while (str[i] && !ft_strchr(cset, str[i]))
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**split_by_str(char *str, char *charset)
{
	char		**res;
	size_t		word_count;
	size_t		i;

	word_count = count_words(str, charset);
	res = malloc(sizeof(char *) * (word_count + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		while (*str && ft_strchr(charset, *str))
			str++;
		if (*str && !ft_strchr(charset, *str))
		{
			res[i] = insert_word(str, charset);
			if (res[i] == NULL)
				return (ptr_2d_free((void ***)&res, i));
			i++;
			while (*str && !ft_strchr(charset, *str))
				str++;
		}
	}
	res[i] = NULL;
	return (res);
}
