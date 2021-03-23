/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_each_parts_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 16:54:09 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/21 21:31:08 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell_bonus.h"

static void		decide_quo_val(char chr[2], char *now)
{
	if (chr[B_SLA] == '\0' && chr[QUO] == '\0' && is_quo(*now))
		chr[QUO] = *now;
	else if (chr[B_SLA] == '\0' && chr[QUO] == *now)
		chr[QUO] = '\0';
	else if (chr[QUO] != '\'' && chr[B_SLA] == '\0' && *now == '\\')
		chr[B_SLA] = '\\';
	else if (chr[QUO] != '\'')
		chr[B_SLA] = ((!chr[B_SLA] && *now == '\\') ? '\\' : '\0');
}

static size_t	count_words(char *str)
{
	size_t		word_count;
	char		chr[2];
	int			flag;

	word_count = 0;
	while (*str)
	{
		chr[QUO] ^= chr[QUO];
		chr[B_SLA] ^= chr[B_SLA];
		if (*str && is_except_separator(str, chr[QUO]))
		{
			str -= 1;
			while (*++str && is_except_separator(str, chr[QUO]))
				decide_quo_val(chr, str);
			word_count++;
		}
		flag ^= flag;
		if (*str && (is_separator(str, NULL)) && (word_count += 1))
			while (*str && (is_separator(str, &flag)))
				str++;
		while (*str && ft_isspace(*str))
			str++;
	}
	return (word_count);
}

static char		*insert_separator(char **str)
{
	char		*word;
	size_t		i;
	int			flag;

	i = 0;
	flag = 0;
	while ((*str)[i] && (is_separator(&(*str)[i], &flag)))
		i++;
	if (!(word = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	flag = 0;
	while (**str && (is_separator(*str, &flag)))
		word[i++] = *(*str)++;
	word[i] = '\0';
	while (**str && ft_isspace(**str))
		(*str)++;
	return (word);
}

static char		*insert_word(char **str)
{
	char		*word;
	size_t		i;
	char		chr[2];

	i = -1;
	chr[QUO] = 0;
	chr[B_SLA] = 0;
	while ((*str)[++i] && (is_except_separator(&(*str)[i], chr[QUO])))
		decide_quo_val(chr, &((*str)[i]));
	if (!(word = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	chr[QUO] = 0;
	chr[B_SLA] = 0;
	while (**str && (is_except_separator(*str, chr[QUO])))
	{
		decide_quo_val(chr, *str);
		word[i++] = **str;
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
	while (*str && i < word_count)
	{
		if (*str && (is_except_separator(str, 0)))
			if (!(res[i++] = insert_word(&str)))
				return (ptr_2d_free((void***)&res, --i));
		if (*str && (is_separator(str, NULL)))
			if (!(res[i++] = insert_separator(&str)))
				return (ptr_2d_free((void***)&res, --i));
	}
	res[i] = NULL;
	return (res);
}
