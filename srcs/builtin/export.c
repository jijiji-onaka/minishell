/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 17:56:17 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/04 02:58:43 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	safe_printf(int check, char *env, t_minishell_info *info)
{
	if (check == 0)
	{
		if (printf("declare -x PWD=%s\n",
				search_env("PWD", 3, info->env)) == -1)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	}
	else if (check == 1)
	{
		if (printf("declare -x OLDPWD=%s\n",
				search_env("OLDPWD", 6, info->env)) == -1)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	}
	else if (check == 2)
	{
		if (printf("declare -x %s\n", env) == -1)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	}
}

static void	display_sorted_env(t_minishell_info *info)
{
	size_t		i;
	char		**env;

	i = 0;
	env = info->environ;
	while (env[i])
		i++;
	merge_strsort(env, 0, i - 1, ft_strcmp);
	i = -1;
	while (env[++i])
	{
		if ((env[i][0] == '_' && env[i][1] == '='))
			continue ;
		if (env[i][0] == 'P' && env[i][1] == 'W' && env[i][2] == 'D' &&
					env[i][3] == '=')
			safe_printf(0, NULL, info);
		else if ((env[i][0] == 'O' && env[i][1] == 'L' && env[i][2] == 'D' &&
					ft_strncmp(env[i] + 3, "PWD", 3) == 0))
			safe_printf(1, NULL, info);
		else
			safe_printf(2, env[i], info);
	}
}

static bool	prepare_in_advance(char *first_arg, t_minishell_info *info, int *j)
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


void		exec_export(t_minishell_info *info, char **args)
{
	char		*env_name;
	char		*env_value;
	int			i;
	int			j;

	if (prepare_in_advance(args[1], info, &j) == false)
		return ;
	while (args[++j])
	{
		if (args[j][0] == '\'' || args[j][0] == '\"')
			if (!(args[j] = re_strtrim(&(args[j]), "\'\"")))
				all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
		if (!(env_name = make_env_name(args[j], &i, info)))
			continue ;
		if (env_name[0] == '$')
			re_strdup(&(env_name),
				search_env(env_name + 1, ft_strlen(env_name + 1), info->env));
		env_value = make_env_value(args, i, &j, info);
		if (env_value[0] == '$')
			re_strdup(&(env_value),
				search_env(env_value + 1, ft_strlen(env_value + 1), info->env));
		update_env_lst(&(info->env), env_name, env_value, info);
		two_free((void**)&env_name, (void**)&env_value);
	}
}
