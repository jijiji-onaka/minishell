/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_make_env_value.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 20:41:03 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/08 07:59:18 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char		*make_env_value(char *arg, t_minishell *info, char **ptr)
{
	int		i;
	char	*res;

	i = -1;
	while (arg[++i])
		;
	if (!(res = malloc(sizeof(char) * (i + 1))))
	{
		ptr_free((void**)ptr);
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	}
	i = 0;
	while (*arg)
	{
		res[i++] = *arg;
		arg++;
	}
	res[i] = '\0';
	return (res);
}

void		add_env_value(t_string *key, t_string *value, t_minishell *info)
{

	char	*search;
	// char	*tmp;

	key->str[key->len - 1] = '\0';
	search = ft_getenv(key->str, info->env, false);
	if (search == NULL)
		return ;
	value->str = re_strjoin(&(value->str), search, value->str);
	if (value->str == NULL)
	{
		ptr_free((void **)&(key->str));
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	}
	value->len += ft_strlen(search);
}
