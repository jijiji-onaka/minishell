/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_is_valid_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 13:58:42 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/13 14:03:24 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bonus_includes/minishell_bonus.h"

static bool	is_parameter(char c)
{
	return (ft_isalnum(c) || c == ' ' || c == '_');
}

static bool	display_err(char *arg, t_minishell *info)
{
	bool	write_err_flag;

	write_err_flag = false;
	if (write(STDERR, "minishell: export: `", 20) < 0)
		write_err_flag = true;
	if (ft_putstr_fd(arg, STDERR) == false)
		write_err_flag = true;
	if (write(STDERR, "\': not a valid identifier\n", 26) < 0)
		write_err_flag = true;
	if (write_err_flag == true)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	g_global.exit_status = 1;
	return (false);
}

bool	is_valid_env_name(char **env_name, char *arg, t_minishell *info)
{
	int		i;
	int		err_flag;

	err_flag = false;
	if (ft_strchr(*env_name, ' ')
		|| (*env_name)[0] == '\0' || (*env_name)[0] == '='
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
