/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 00:06:42 by tjinichi          #+#    #+#             */
/*   Updated: 2021/05/13 01:19:18 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	setting_1(char ***environ, char **paths, char ***split,
					t_minishell *info)
{
	int	i;

	if (info->minishell_op_c == false)
		tcsetattr(STDIN, TCSANOW, &(info->terminal[ORIGINAL]));
	*environ = get_environ(info->env, info);
	*paths = ft_getenv("PATH", info->env, false);
	// printf("path : [%s]\n", *paths);
	i = 0;
	*paths = ft_strdup(*paths);
	if (*paths && (*paths)[0] != '\0')
	{
		if (*paths == NULL)
			all_free_exit(info, ERR_MALLOC, LINE, FILE);
		while ((*paths)[i] == '\\')
			i++;
		if ((*paths)[0] == ':')
		{
			*paths = re_strjoin(paths, ".", *paths);
			if (*paths == NULL)
				all_free_exit(info, ERR_MALLOC, LINE, FILE);
		}
		else if ((*paths)[ft_strlen(*paths) - 1] == ':')
		{
			*paths = re_strjoin(paths, *paths, ".");
			if (*paths == NULL)
				all_free_exit(info, ERR_MALLOC, LINE, FILE);
		}
		if ((*paths)[0] != '\0')
			*split = ft_split(*paths, ':');
	}
	else
		*split = NULL;
	g_global.exit_status = 0;
}

int	setting_2(char *paths, char **command, char ***split, t_minishell *info)
{
	int		i;
	char	*tmp;
	size_t	len;

	i = -1;
	if (ft_strchr((*command), '/') == NULL)
		while ((*split)[++i])
		{
			// if ((*split)[i][0] == '.')
			// 	*command = re_strjoin(command, "./", *command);
			// printf("[%s]\n", (*split)[i]);
			tmp = check_executable_file_in_bin_dir((*split)[i], command, info);
			// printf("[%s]\n", tmp);
			if (tmp)
			{
				free((*split)[i]);
				(*split)[i] = tmp;
			}
		}
	// if (ft_strchr(command, '/'))
	// {
	// 	(*split)[i] = ft_strdup(command);
	// 	if ((*split)[i] == NULL)
	// 		all_free_exit(info, ERR_MALLOC, LINE, FILE);
	// }
	(void)paths;
	// len = ft_strlen(paths);
	(void)len;
	// if ((paths[len - 1] == ':' || paths[len - 1] == '/')
	// 	&& no_exe_file_in_bin_dir((*split)[i], info) == true)
	// 	(*split)[i] = re_strjoin(&((*split)[i]), "./", (*split)[i]);
	// if ((*split)[i] == NULL)
	// 	all_free_exit(info, ERR_MALLOC, LINE, FILE);
	return (i);
}
