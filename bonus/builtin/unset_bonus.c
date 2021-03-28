/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 18:44:56 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/24 00:41:42 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

static bool	display_err(char *s, t_minishell *info)
{
	if (write(STDERR_FILENO, "minishell: unset: `", 19) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (write(STDERR_FILENO, s, ft_strlen(s)) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (write(STDERR_FILENO, "': not a valid identifier\n", 26) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	g_global.exit_status = 1;
	return (false);
}

static bool	is_valid_env_name(char *env_name, t_minishell *info)
{
	int		i;
	int		err_flag;

	err_flag = false;
	if (ft_isspace((env_name)[0]) || env_name[0] == '\0')
		err_flag = true;
	i = 0;
	while ((env_name)[++i])
		if (!is_parameter((env_name)[i]))
			err_flag = true;
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
	if (args[1] == NULL)
		return ;
	if (args[1][0] == '-')
		return (error_mandatory(ERR_UNSET, 29, info));
	i = 0;
	valid_flag = false;
	while (args[++i])
		valid_flag = is_valid_env_name(args[i], info);
	if (!valid_flag)
		return ;
	i = 0;
	while (args[++i])
		remove_env_lst_if(&(info->env), args[i]);
	g_global.exit_status = 0;
}
