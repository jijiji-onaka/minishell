/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 17:56:17 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 21:54:26 by tjinichi         ###   ########.fr       */
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

// static void	only_argument(char **args, int j)
// {
// 	if (j == 1)
// 		return ;

// }

void		exec_export(t_minishell_info *info, char **args)
{
	char		*env_name;
	int			i;
	int			j;

	if (args[1] == NULL)
		return (display_sorted_env(info));
	if (args[1][0] == '-')
		return (error_mandatory(ERR_EXPORT, 30, info));
	j = 0;
	while (args[j + 1])
		j++;
	i = 0;
	while (args[j][i] && args[j][i] != '=')
		i++;
	if (args[j][i] == '\0')
	{
		puts("未実装");
		// return (only_argument(args, j));
		return ;
	}
	if (!(env_name = malloc(i + 1)))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	i = -1;
	while (args[j][++i] != '=')
		env_name[i] = args[j][i];
	env_name[i] = '\0';
	update_env_lst(&(info->env), env_name, args[j] + i, info);
	ptr_free((void **)&env_name);
}
