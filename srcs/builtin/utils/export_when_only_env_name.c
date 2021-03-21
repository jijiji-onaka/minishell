/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_when_only_env_name.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 12:38:30 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/21 14:55:41 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static bool	display_err(char *arg, t_minishell *info)
{
	bool write_err_flag;

	write_err_flag = false;
	if (write(2, "minishell: export: `", 20) < 0)
		write_err_flag = true;
	if (ft_putstr_fd(arg, 2) == false)
		write_err_flag = true;
	if (write(2, "\': not a valid identifier\n", 26) < 0)
		write_err_flag = true;
	if (write_err_flag == true)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	g_signal.exit_status = 1;
	return (false);
}

static bool	is_valid_env_name(char **env_name, char *arg, t_minishell *info)
{
	int		i;
	int		err_flag;

	err_flag = false;
	if (ft_strchr(*env_name, ' ') ||
	(*env_name)[0] == '\0' || (*env_name)[0] == '=' ||
		ft_isdigit((*env_name)[0]))
		err_flag = true;
	if (err_flag)
		return (display_err(arg, info));
	i = -1;
	while ((*env_name)[++i])
	{
		if (!is_parameter((*env_name)[i]))
			err_flag = true;
	}
	if (err_flag)
		return (display_err(arg, info));
	return (true);
}

void		when_only_env_name(char *arg, t_minishell *info)
{
	char	*env_name;
	bool	f;

	if (!(env_name = ft_strdup(arg)))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	if (is_valid_env_name(&env_name, arg, info))
	{
		if (ft_strcmp(arg, "PWD") == 0)
		{
			search_env("PWD", 3, info->env, &f);
			if (!f)
				update_env_lst(&(info->env), env_name,
					info->current_dir_path, info);
		}
		else if (ft_strcmp(arg, "OLDPWD") == 0)
		{
			if (!search_env(env_name, ft_strlen(env_name), info->env, &f) && !f)
				update_env_lst(&(info->env), env_name, info->oldpwd_path, info);
		}
		else if (!search_env(env_name, ft_strlen(env_name), info->env, &f)
			&& !f)
			update_env_lst(&(info->env), env_name, NULL, info);
	}
	ptr_free((void**)&env_name);
}
