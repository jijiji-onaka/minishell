/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_free_exit_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 02:54:08 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/21 14:17:22 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

static void		free_env_lst(t_envlst **envlst)
{
	t_envlst	*env_tmp;

	while (*envlst)
	{
		env_tmp = (*envlst)->next;
		ptr_free((void **)&((*envlst)->value));
		ptr_free((void **)&(*envlst));
		*envlst = env_tmp;
	}
}

static void		free_cmd_lst(t_cmdlst **cmdlst)
{
	t_cmdlst	*cmdlst_tmp;
	size_t		i;

	i = 0;
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

void			all_free_minishell_info(t_minishell *info)
{
	ptr_free((void**)&(info->current_dir_path));
	ptr_free((void**)&(info->oldpwd_path));
	free_cmd_lst(&(info->cmd_lst));
	free_env_lst(&(info->env));
}

static void		put_error_location_and_exit(char *error_message,
			int line_num, char *file_name, t_minishell *info)
{
	char	*location_message;
	char	*tmp;

	red_error();
	if (write(STDERR_FILENO, info->current_dir_path,
				ft_strlen(info->current_dir_path)) < 0)
		exit(EXIT_FAILURE);
	if (!(location_message = ft_str3join("/", file_name, ":")))
		ft_perror_exit(ERR_MALLOC);
	tmp = location_message;
	if (!(location_message = strjoin_num(location_message, line_num)))
		ft_perror_exit(ERR_MALLOC);
	ptr_free((void **)&tmp);
	ft_putendl_fd(location_message, STDERR_FILENO);
	ptr_free((void **)&location_message);
	free_env_lst(&(info->env));
	ptr_free((void**)&(info->current_dir_path));
	ft_perror_exit(error_message);
}

void			all_free_exit(t_minishell *info, char *error_message, \
					int line_num, char *file_name)
{
	if (info == NULL)
		signal_error_exit();
	if (info->ptr_2d_for_free)
		ptr_2d_free((void***)&info->ptr_2d_for_free, -1);
	if (info->ptr_for_free)
		ptr_free((void**)&info->ptr_for_free);
	if (info->ptr_for_free_2)
		ptr_free((void**)&info->ptr_for_free_2);
	free_cmd_lst(&(info->cmd_lst));
	if (errno == 0)
		exit(1);
	put_error_location_and_exit(error_message, line_num, file_name, info);
}