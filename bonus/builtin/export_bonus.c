/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 17:56:17 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/24 00:41:42 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

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
	g_global.exit_status = 1;
	return (false);
}

static bool	is_valid_env_name(char **env_name, char *arg, t_minishell *info)
{
	int		i;
	int		err_flag;

	err_flag = false;
	if (ft_strchr(*env_name, ' ') ||
	(*env_name)[0] == '\0' || (*env_name)[0] == '='
		|| ft_isdigit((*env_name)[0]))
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

static bool	preparation(char *first_arg, t_minishell *info, int *j)
{
	if (first_arg == NULL)
	{
		display_sorted_env(info);
		return (false);
	}
	if (first_arg[0] == '-')
	{
		error_mandatory(ERR_EXPORT, 30, info);
		return (false);
	}
	*j = 0;
	return (true);
}

static char	*apply_env_value(char *arg, t_minishell *info, char **env_name)
{
	char	*env_value;

	if (arg[0] == '+' && arg[1] == '=')
		env_value = add_env_value(arg + 2, info, env_name);
	else
		env_value = make_env_value(arg + 1, info, env_name);
	return (env_value);
}

void		exec_export(t_minishell *info, t_cmdlst *cmd)
{
	char		*env_name;
	char		*env_value;
	char		**args;
	int			i;
	int			j;

	args = cmd->arg;
	g_global.exit_status = 0;
	if (preparation(args[1], info, &j) == false)
		return ;
	while (args[++j])
	{
		if (!(env_name = make_env_name(args[j], &i, info)))
		{
			when_only_env_name(args[j], info);
			continue ;
		}
		env_value = apply_env_value(args[j] + i, info, &env_name);
		if (is_valid_env_name(&env_name, args[j], info))
			update_env_lst(&(info->env), env_name, env_value, info);
		two_free((void**)&env_name, (void**)&env_value);
	}
}
