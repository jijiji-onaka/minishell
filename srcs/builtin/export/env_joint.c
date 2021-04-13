/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_joint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 20:41:03 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/10 14:06:40 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	joint_env_value(t_string *key, t_string *value, t_minishell *info)
{
	char	*search;

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
