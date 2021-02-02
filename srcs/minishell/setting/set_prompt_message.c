/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_prompt_message.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 01:50:40 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 16:49:28 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	set_prompt_message(t_envlst *env_lst)
{
	char *s;

	s = search_env("USER", 4, env_lst);
	g_user_name = s;
	g_user_name_count = 0;
	while (g_user_name[g_user_name_count])
		g_user_name_count++;
	s = search_env("PWD", 3, env_lst);
	g_working_dir = s;
}
