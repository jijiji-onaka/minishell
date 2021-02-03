/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 17:56:17 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/03 21:47:55 by tjinichi         ###   ########.fr       */
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
//export a='b c"a"'
	if (prepare_in_advance(args[1], info, &j) == false)
		return ;
	while (args[++j])
	{
		i = 0;
		while (args[j][i] && args[j][i] != '=')
			i++;
		if (args[j][i] == '\0')
			continue ;
		if (!(env_name = malloc(i + 2)))
			all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
		i = -1;
		while (args[j][++i] != '=')
			env_name[i] = args[j][i];
		env_name[i++] = '=';
		env_name[i] = '\0';
		printf("%s\n", env_name);
		exit(1);
		env_value = make_env_value(args, i, &j, info);
		update_env_lst(&(info->env), env_name, env_value, info);
		ptr_free((void **)&env_name);
		ptr_free((void **)&env_value);
	}
}
