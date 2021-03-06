/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 02:54:08 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/13 14:03:38 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../bonus_includes/minishell_bonus.h"

static void	signal_error_exit(void)
{
	red_error();
	write(STDERR, "signal function error\n", 22);
	exit(EXIT_FAILURE);
}

static void	put_error_location_and_exit(char *error_message,
				int line_num, char *file_name, t_minishell *info)
{
	char	*location_message;
	char	*tmp;

	red_error();
	if (write(STDERR, info->current_dir_path,
			ft_strlen(info->current_dir_path)) < 0)
		exit(EXIT_FAILURE);
	location_message = ft_str3join("/", file_name, ":");
	if (location_message == NULL)
		ft_perror_exit(ERR_MALLOC);
	tmp = location_message;
	location_message = strjoin_num(location_message, line_num);
	if (location_message == NULL)
		ft_perror_exit(ERR_MALLOC);
	ptr_free((void **)&tmp);
	ft_putendl_fd(location_message, STDERR);
	ptr_free((void **)&location_message);
	free_env_lst(&(info->env));
	ptr_free((void **)&(info->current_dir_path));
	ptr_free((void **)&(info->oldpwd_path));
	ft_perror_exit(error_message);
}

void	all_free_exit(t_minishell *info, char *error_message,
						int line_num, char *file_name)
{
	if (info == NULL)
		signal_error_exit();
	if (info->ptr_2d_for_free)
		ptr_2d_free((void ***)&info->ptr_2d_for_free, -1);
	if (info->ptr_for_free)
		ptr_free((void **)&info->ptr_for_free);
	if (info->ptr_for_free_2)
		ptr_free((void **)&info->ptr_for_free_2);
	ptr_free((void **)&(info->key.target));
	free_cmd_lst(&(info->cmd_lst));
	if (errno == 0)
		exit(1);
	put_error_location_and_exit(error_message, line_num, file_name, info);
}

void	ft_perror_exit(char *error_message)
{
	ft_perror(error_message);
	exit(EXIT_FAILURE);
}
