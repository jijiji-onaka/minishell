/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_each_parts_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 16:54:09 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/13 14:03:24 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bonus_includes/minishell_bonus.h"

static void	decide_quo_val(char chr[2], char *now)
{
	if (chr[B_SLA] == '\0' && chr[QUO] == '\0' && is_quo(*now))
		chr[QUO] = *now;
	else if (chr[B_SLA] == '\0' && chr[QUO] == *now)
		chr[QUO] = '\0';
	else if (chr[QUO] != '\'' && chr[B_SLA] == '\0' && *now == '\\')
		chr[B_SLA] = '\\';
	else if (chr[QUO] != '\'')
	{
		if (chr[B_SLA] == '\0' && *now == '\\')
			chr[B_SLA] = '\\';
		else
			chr[B_SLA] = '\0';
	}
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
		if (*str && (is_separator(str, NULL)) && (word_count++))
			while (*str && (is_separator(str, &flag)))
				str++;
		while (*str && ft_isspace(*str))
			str++;
	}
	return (word_count);
}

static char	*insert_separator(char **str)
{
	char		*word;
	size_t		i;
	int			flag;

	i = 0;
	flag = 0;
	while ((*str)[i] && (is_separator(&(*str)[i], &flag)))
		i++;
	word = malloc(sizeof(char) * (i + 1));
	if (word == NULL)
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

static char	*insert_word(char **str)
{
	char		*word;
	size_t		i;
	char		chr[2];

	i = -1;
	chr[QUO] = 0;
	chr[B_SLA] = 0;
	while ((*str)[++i] && (is_except_separator(&(*str)[i], chr[QUO])))
		decide_quo_val(chr, &((*str)[i]));
	word = malloc(sizeof(char) * (i + 1));
	if (word == NULL)
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

char	**split_each_parts(char *str)
{
	char		**res;
	size_t		i[2];

	i[1] = count_words(str);
	res = malloc(sizeof(char *) * (i[1] + 1));
	if (res == NULL)
		return (NULL);
	i[0] = 0;
	while (*str && i[0] < i[1])
	{
		if (*str && (is_except_separator(str, 0)))
		{
			res[i[0]] = insert_word(&str);
			if (res[i[0]++] == NULL)
				return (ptr_2d_free((void ***)&res, --i[0]));
		}
		if (*str && (is_separator(str, NULL)))
		{
			res[i[0]] = insert_separator(&str);
			if (res[i[0]++] == NULL)
				return (ptr_2d_free((void ***)&res, --i[0]));
		}
	}
	res[i[0]] = NULL;
	return (res);
}
