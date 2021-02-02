/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_each_parts.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 16:54:09 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 17:29:41 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static size_t	count_words(char *str)
{
	size_t		word_count;
	int			flag;

	word_count = 0;
	flag = 0;
	while (*str)
	{
		while (*str && (isalnum_except_next_redir(str) ||
						*str == ' ') && (flag = 1))
			str++;
		if (*str && !(isalnum_except_next_redir(str) || *str == ' '))
		{
			if (flag == 1)
				word_count += 2;
			else
				word_count++;
			flag = 0;
			while (*str && !(isalnum_except_next_redir(str) || *str == ' '))
				str++;
		}
	}
	return (word_count + flag);
}

static char		*re_insert_redirect(char **old, char **str)
{
	char	*res;
	int		i;

	i = 0;
	while ((*str)[i] && ft_isalnum((*str)[i]))
		i++;
	if (!(res = malloc(ft_strlen(*old) + i + 2)))
		return (NULL);
	i = -1;
	while ((*old)[++i])
		res[i] = (*old)[i];
	res[i++] = ' ';
	while (**str && ft_isalnum(**str))
	{
		res[i++] = **str;
		(*str)++;
	}
	res[i] = '\0';
	ptr_free((void **)old);
	return (res);
}

static char		*insert_word(char **str)
{
	char		*word;
	size_t		i;

	i = 0;
	while ((*str)[i] && !(isalnum_except_next_redir(&(*str)[i]) ||
				(*str)[i] == ' '))
		i++;
	if (!(word = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (**str && !(isalnum_except_next_redir(*str) || **str == ' '))
	{
		word[i] = **str;
		i++;
		(*str)++;
	}
	word[i] = '\0';
	return (word);
}

static char		*insert_separator(char **str)
{
	char		*word;
	size_t		i;

	i = 0;
	while ((*str)[i] && (isalnum_except_next_redir(&(*str)[i]) ||
				(*str)[i] == ' '))
		i++;
	if (!(word = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (**str && (isalnum_except_next_redir(*str) || **str == ' '))
	{
		word[i] = **str;
		i++;
		(*str)++;
	}
	word[i] = '\0';
	return (word);
}

char			**split_each_parts(char *str)
{
	char		**res;
	size_t		word_count;
	size_t		i;

	word_count = count_words(str);
	if (!(res = malloc(sizeof(char *) * (word_count + 1))))
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		if (*str && (isalnum_except_next_redir(str) || *str == ' '))
			if (!(res[i++] = insert_separator(&str)))
				return (ptr_2d_free((void***)&res, --i));
		if (*str && !(isalnum_except_next_redir(str) || *str == ' '))
			if (!(res[i++] = insert_word(&str)))
				return (ptr_2d_free((void***)&res, --i));
		if (i == 1 && res[0][0] == '>')
			if (!(res[0] = re_insert_redirect(&(res[0]), &str)))
				return (ptr_2d_free((void***)&res, --i));
	}
	res[i] = NULL;
	return (res);
}
