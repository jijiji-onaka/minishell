/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 18:44:56 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/21 07:01:38 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	display_err(char *s, t_minishell *info)
{
	if (write(STDERR_FILENO, "minishell: unset: `", 19) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (write(STDERR_FILENO, s, ft_strlen(s)) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (write(STDERR_FILENO, "': not a valid identifier\n", 26) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	g_signal.exit_status = 1;
	return (false);
}

static bool	is_valid_env_name(char *env_name, t_minishell *info)
{
	int		i;
	int		err_flag;

	err_flag = false;
	if (ft_strchr(env_name, ' ') ||
	(env_name)[0] == '\0' || (env_name)[0] == '=' || ft_isdigit((env_name)[0]))
		err_flag = true;
	if (err_flag)
		return (display_err(env_name, info));
	i = -1;
	while ((env_name)[++i])
	{
		if (!is_parameter((env_name)[i]))
			err_flag = true;
	}
	if (err_flag)
		return (display_err(env_name, info));
	return (true);
}

void		exec_unset(t_minishell *info, t_cmdlst *cmd)
{
	int		i;
	bool	valid_flag;
	char	**args;

	args = cmd->arg;
	g_signal.exit_status = 0;
	if (args[1] == NULL)
		return ;
	if (args[1][0] == '-')
		return (error_mandatory(ERR_UNSET, 29, info));
	i = 0;
	valid_flag = false;
	while (args[++i])
	{
		if (is_valid_env_name(args[i], info))
			remove_env_lst_if(&(info->env), args[i]);
	}
}
