/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 10:30:25 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/22 02:08:37 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/string_func.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;
	size_t			mini_len;

	if (s == NULL)
		return (NULL);
	if (!(start == 0 && s[0] == '\0') && ft_strlen(s) <= start)
		return (ft_strdup(""));
	mini_len = ft_strlen(&s[start]);
	if (mini_len < len)
		len = mini_len;
	if (!(str = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[i + start];
		i++;
	}
	str[i] = '\0';
	return (str);
}
