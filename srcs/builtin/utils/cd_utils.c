/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 12:11:59 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/08 07:58:39 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void		upper_dir(char *now, t_minishell *info)
{
	char	*res;
	int		i[2];

	i[0] = -1;
	i[1] = -1;
	while (now[++i[0]])
		if (now[i[0]] == '/' && now[i[0] + 1] != '/'
		&& now[i[0] + 1] != '.' && now[i[0] + 1] != '\0')
			i[1] = i[0];
	if (i[1] == -1)
		i[1] = i[0];
	else if (i[1] == 0 || i[1] == 1)
		i[1] += 1;
	if (!(res = malloc(sizeof(char) * (i[1] + 1))))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	i[0] = -1;
	while (now[++i[0]])
	{
		res[i[0]] = now[i[0]];
		if (i[0] == i[1])
			break ;
	}
	res[i[0]] = '\0';
	ptr_free((void**)&(info->current_dir_path));
	info->current_dir_path = res;
}

void		go_to_upper_dir(char *now, t_minishell *info)
{
	int		i;
	char	**split;
	// bool	flag;

	i = -1;
	upper_dir(now, info);
	if (!(split = ft_split(now, '/')))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	info->ptr_2d_for_free = split;
	while (split[++i])
	{
		if (ft_strcmp(split[i], ".") == 0)
			go_to_cwd(info, info->current_dir_path, now);
		else if (ft_strcmp(split[i], "..") == 0)
			upper_dir(info->current_dir_path, info);
	}
	ptr_2d_free((void***)&(split), -1);
	info->ptr_2d_for_free = NULL;
}

bool		is_symbolic_dir(t_minishell *info, char *dir_name)
{
	t_stat	stat_buf;

	if (lstat(dir_name, &stat_buf) == -1)
	{
		if (errno == EFAULT || errno == ELOOP || errno == ENOMEM)
			all_free_exit(info, ERR_LSTAT, __LINE__, __FILE__);
		return (false);
	}
	if (S_ISLNK(stat_buf.st_mode) == false || S_ISDIR(stat_buf.st_mode))
		return (false);
	return (true);
}

void		connect_path(char **src, char *dst, t_minishell *info)
{
	if ((*src)[ft_strlen(*src) - 1] != '/')
		*src = re_str3join(src, *src, "/", dst);
	else
		*src = re_strjoin(src, *src, dst);
	if (!(*src))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
}

bool		not_found_cwd(t_minishell *info, char *arg_dir, char ***ptr)
{
	if (errno != ENOENT)
		all_free_exit(info, ERR_GETCWD, __LINE__, __FILE__);
	write(STDERR, "cd: error retrieving current directory: getcwd: \
cannot access parent directories: No such file or directory\n", 108);
	update_env_value(&(info->env), "OLDPWD",
					info->current_dir_path, info);
	connect_path(&(info->current_dir_path), arg_dir, info);
	update_env_value(&(info->env), "PWD", info->current_dir_path, info);
	// info->cwd_err_f = 1;
	if (ptr)
		ptr_2d_free((void***)(ptr), -1);
	return (false);
}
