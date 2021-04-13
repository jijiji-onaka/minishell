/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 15:05:01 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/10 15:22:09 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_env_lst(t_envlst **envlst)
{
	t_envlst	*env_tmp;

	while (*envlst)
	{
		env_tmp = (*envlst)->next;
		ptr_free((void **)&((*envlst)->env.key));
		ptr_free((void **)&((*envlst)->env.value));
		ptr_free((void **)&(*envlst));
		*envlst = env_tmp;
	}
}

void	free_cmd_lst(t_cmdlst **cmdlst)
{
	t_cmdlst	*cmdlst_tmp;

	while (*cmdlst)
	{
		cmdlst_tmp = (*cmdlst)->next;
		if ((*cmdlst)->arg)
		{
			ptr_2d_free((void ***)&((*cmdlst)->arg), -1);
		}
		ptr_free((void **)&(*cmdlst));
		*cmdlst = cmdlst_tmp;
	}
}

void	free_command_history(t_hist_list **history)
{
	t_hist_list	*next;

	while (*history)
	{
		next = (*history)->old_hist;
		ptr_free((void **)&((*history)->command));
		free(*history);
		*history = next;
	}
}

void	all_free_minishell_info(t_minishell *info)
{
	ptr_free((void **)&(info->current_dir_path));
	ptr_free((void **)&(info->oldpwd_path));
	ptr_free((void **)&(info->key.target));
	free_cmd_lst(&(info->cmd_lst));
	free_env_lst(&(info->env));
	free_command_history(&(info->history.begin));
}
