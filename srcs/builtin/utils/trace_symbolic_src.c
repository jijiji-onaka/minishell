/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_symbolic_src.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 01:02:59 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 17:00:00 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*change_to_symbolic_source(char *dir_name, t_minishell_info *info)
{
	char		*res;
	int			i;
	int			j;

	i = 0;
	while (info->current_dir_path[i])
		i++;
	j = 0;
	while (dir_name[j])
		j++;
	if (!(res = malloc(i + j + 2)))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	i = -1;
	while (info->current_dir_path[++i])
		res[i] = info->current_dir_path[i];
	res[i++] = '/';
	j = 0;
	while (dir_name[j])
	{
		res[i + j] = dir_name[j];
		j++;
	}
	res[i + j] = '\0';
	return (res);
}

void		trace_symbolic_src(t_minishell_info *info, char *dir_name)
{
	char	*symbolic_src;

	symbolic_src = change_to_symbolic_source(dir_name, info);
	ptr_free((void **)&(info->current_dir_path));
	info->current_dir_path = symbolic_src;
	if (chdir(symbolic_src) == -1)
	{
		if (errno == EFAULT || errno == EIO || errno == ENOMEM)
			all_free_exit(info, ERR_CHDIR, __LINE__, __FILE__);
	}
	update_env_lst(&(info->env), "PWD=", info->current_dir_path, info);
}
