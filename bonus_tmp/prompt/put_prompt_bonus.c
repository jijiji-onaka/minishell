/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_prompt_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 00:41:03 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/21 20:31:16 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

void		put_prompt(t_minishell *info)
{
	char	*user_name;
	char	*working_dir;

	user_name = search_env("USER", 4, info->env, NULL);
	working_dir = info->current_dir_path;
	if (!user_name)
	{
		if (write(STDERR_FILENO, "Who am I?", 9) < 0)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	}
	else if (write(STDERR_FILENO, user_name, ft_strlen(user_name)) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (write(STDERR_FILENO, "\033[1m\x1b[35m (;;) \x1b[0m", 19) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (!working_dir)
	{
		if (write(STDERR_FILENO, "Where am I?", 11) < 0)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	}
	else if (write(STDERR_FILENO, working_dir, ft_strlen(working_dir)) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (write(STDERR_FILENO, "\033[1m\x1b[35m (;;) > \x1b[0m", 21) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
}
