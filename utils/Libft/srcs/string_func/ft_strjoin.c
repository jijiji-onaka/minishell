/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 10:46:43 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/11 21:26:11 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/string_func.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*str;
	size_t		len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(str = malloc(sizeof(char) * (len))))
		return (NULL);
	ft_strlcpy(str, s1, len);
	ft_strlcat(str, s2, len);
	return (str);
}
