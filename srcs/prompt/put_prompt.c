/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 00:41:03 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/28 18:09:46 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		put_prompt(t_minishell *info)
{
	char	*user_name;
	char	*working_dir;

	if (isatty(STDIN_FILENO) == false)
		return ;
	user_name = ft_getenv("USER", info->env, false);
	working_dir = info->current_dir_path;
	if (!user_name)
	{
		if (write(STDIN_FILENO, "Who am I?", 9) < 0)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	}
	else if (write(STDIN_FILENO, user_name, ft_strlen(user_name)) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (write(STDIN_FILENO, "\033[1m\x1b[35m (;;) \x1b[0m", 19) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (!working_dir)
	{
		if (write(STDIN_FILENO, "Where am I?", 11) < 0)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	}
	else if (write(STDIN_FILENO, working_dir, ft_strlen(working_dir)) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (write(STDIN_FILENO, "\033[1m\x1b[35m (;;) > \x1b[0m", 21) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
}
