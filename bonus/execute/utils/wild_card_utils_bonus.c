/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 02:04:17 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/18 04:47:30 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell_bonus.h"

bool		pattern_match(char *s1, char *s2)
{
	if (s1[0] == '\0' && s2[0] == '\0')
		return (true);
	if (s1[0] == '*')
	{
		if (s2[0] == '\0')
			return (pattern_match(&s1[1], &s2[0]));
		else
		{
			if (pattern_match(&s1[1], &s2[0]) == true)
				return (true);
			else
				return (pattern_match(&s1[0], &s2[1]));
		}
	}
	if (s1[0] == s2[0])
		return (pattern_match(&s1[1], &s2[1]));
	return (false);
}

size_t		word_count(char const *s, char c)
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
