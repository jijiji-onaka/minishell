/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_switch_env_value.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 03:42:25 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 21:13:51 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*check_dollar_in_one_word(char *s, char c)
{
	char	*s_tmp;

	s_tmp = s;
	while (*s_tmp && *s_tmp != ' ')
	{
		if (*s_tmp == c)
			return (s_tmp);
		s_tmp++;
	}
	if (*s_tmp == '\0' && c == '\0')
		return (s_tmp);
	return (NULL);
}

int			switch_env_value(char **s, char **res, t_envlst *env_lst)
{
	char	*dollar_ptr;
	char	*sub;

	if (!(dollar_ptr = check_dollar_in_one_word(*s, '$')))
		return (1);
	if ((*(*(s) + 1) == '$') || (*(*(s) + 1) == '\0'))
		return (1);
	if (**s == '\\' && *(*(s) + 1) == '$')
		return ((*s)++ || 1);
	else if (**s == '$' && *(*(s) + 1) == '?')
	{
		(*s) += 2;
		if (!(*res = numjoin_str(*s, g_signal.exit_status)))
			return (-2);
		return (-1);
	}
	sub = ft_substr(*s, 0, dollar_ptr - *s);
	char	*tmp = search_env((dollar_ptr) + 1, ft_strlen(dollar_ptr) + 1, env_lst);
	if (tmp == NULL)
		return (1);
	if (!(*res = ft_strjoin(sub, tmp)))
	{
		ptr_free((void**)&sub);
		return (-2);
	}
	ptr_free((void**)&sub);
	return (-1);
}
