/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_each_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 14:32:44 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/21 05:14:55 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static bool		is_arg(char c, char quo)
{
	if (quo != 0 && !(quo != 0 && c != quo))
		return (0);
	if (quo <= 0 && c && ft_iswhitespace((c)))
		return (1);
	return (0);
}

static char		decide_quo_val(char quo, char now, char *sla)
{
	if (quo == 0 && is_quo(now) && *sla == 0)
		quo = now;
	else if (quo != 0 && quo == now && *sla == 0)
		quo = 0;
	if (now == '\\' && sla && quo != '\'')
		*sla = '\\';
	else
		*sla = 0;
	return (quo);
}

static size_t	count_words(char *str)
{
	size_t		word_count;
	char		quo;
	char		sla;

	word_count = 0;
	quo = 0;
	while (*str)
	{
		while (*str && ((is_arg(*str, -1))))
			str++;
		if (*str && !(is_arg(*str, 0)))
		{
			word_count++;
			quo ^= quo;
			sla ^= sla;
			while (*str && !(is_arg(*str, quo)))
			{
				quo = decide_quo_val(quo, *str, &sla);
				str++;
			}
		}
	}
	return (word_count);
}

static char		*insert_word(char **str)
{
	char		*word;
	size_t		i;
	char		quo;
	char		sla;

	i = -1;
	quo = 0;
	sla = 0;
	while ((*str)[++i] && !(is_arg((*str)[i], quo)))
		quo = decide_quo_val(quo, (*str)[i], &sla);
	if (!(word = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	quo = 0;
	sla = 0;
	while (**str && !(is_arg(**str, quo)))
	{
		quo = decide_quo_val(quo, **str, &sla);
		word[i++] = **str;
		(*str)++;
	}
	word[i] = '\0';
	return (word);
}

char			**split_each_arg(char *str)
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
		while (*str && is_arg(*str, -1))
			str++;
		if (*str && !(ft_isspace(*str)))
			if (!(res[i++] = insert_word(&str)))
				return (ptr_2d_free((void***)&res, --i));
	}
	res[i] = NULL;
	return (res);
}
