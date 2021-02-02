/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_free_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 02:54:08 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 20:48:36 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		while ((*cmdlst)->arg[i])
			i++;
		ptr_2d_free((void ***)&((*cmdlst)->arg), i);
		ptr_free((void **)&(*cmdlst));
		*cmdlst = cmdlst_tmp;
	}
}

void			all_free_minishell_info(t_minishell_info *info)
{
	// ptr_free((void**)&(info->current_dir_path));
	free_cmd_lst(&(info->cmd_lst));
	free_env_lst(&(info->env));
}

static void		put_error_location_and_exit(char *error_message,
			int line_num, char *file_name, t_minishell_info *info)
{
	char	*location_message;
	char	*tmp;

	red_error();
	if (write(STDERR_FILENO, g_working_dir, ft_strlen(g_working_dir)) < 0)
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
	ft_perror_exit(error_message);
}

void			all_free_exit(t_minishell_info *info, char *error_message, \
					int line_num, char *file_name)
{
	if (info == NULL)
		signal_error_exit();
	ptr_free((void**)&(info->current_dir_path));
	free_cmd_lst(&(info->cmd_lst));
	ptr_2d_free((void ***)&(info->environ), 0);
	if (errno == 0)
		exit(1);
	put_error_location_and_exit(error_message, line_num, file_name, info);
}
