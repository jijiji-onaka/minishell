/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 17:56:17 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/25 02:40:19 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	display_err(char *arg, t_minishell *info)
{
	bool write_err_flag;

	write_err_flag = false;
	if (write(STDERR_FILENO, "minishell: export: `", 20) < 0)
		write_err_flag = true;
	if (ft_putstr_fd(arg, 2) == false)
		write_err_flag = true;
	if (write(STDERR_FILENO, "\': not a valid identifier\n", 26) < 0)
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

static bool	preparation(char *first_arg, t_minishell *info, int *i)
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
	*i = 0;
	return (true);
}

static t_string		make_key(char *src, t_minishell *info)
{
	t_string	res;

	if (src == NULL)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	res.str = src;
	res.len = ft_strlen(src);
	return (res);
}

static t_string		make_value(char *src, bool is_val, t_minishell *info)
{
	t_string	res;

	if (is_val)
	{
		res.str = NULL;
		res.len = 0;
		return (res);
	}
	res.str = ft_strdup(src);
	if (res.str == NULL)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	res.len = ft_strlen(src);
	return (res);
}

void		exec_export(t_minishell *info, t_cmdlst *cmd)
{
	t_string	key;
	t_string	value;
	int			i;
	char		*equ_ptr;
	size_t		key_len;

	g_global.exit_status = 0;
	if (preparation(cmd->arg[1], info, &i) == false)
		return ;
	while (cmd->arg[++i])
	{
		equ_ptr = ft_strchr(cmd->arg[i] + 1, '=');
		if (equ_ptr == NULL)
			key_len = -1;
		else
			key_len = equ_ptr - cmd->arg[i];
		key = make_key(ft_substr(cmd->arg[i], 0, key_len), info);
		value = make_value(cmd->arg[i] + key_len + 1, equ_ptr == NULL, info);
		if (equ_ptr && key.str[key.len - 1] == '+')
			add_env_value(&key, &value, info);
		if (is_valid_env_name(&(key.str), cmd->arg[i], info))
			update_env_lst(&(info->env), key, value, info);
		else
			two_free((void **)&(key.str), (void **)&(value.str));
	}
}
