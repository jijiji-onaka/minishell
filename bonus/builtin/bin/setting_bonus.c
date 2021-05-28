/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 00:06:42 by tjinichi          #+#    #+#             */
/*   Updated: 2021/05/24 22:32:10 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bonus_includes/minishell_bonus.h"

static void	setting_1_5(t_minishell *info)
{
	if (signal(SIGQUIT, &sig_nothing) == SIG_ERR)
		all_free_exit(info, ERR_SIGNAL, __LINE__, __FILE__);
	if (signal(SIGINT, &sig_nothing) == SIG_ERR)
		all_free_exit(info, ERR_SIGNAL, __LINE__, __FILE__);
}

void	setting_1(char ***environ, char **paths, char ***split,
					t_minishell *info)
{
	if (info->minishell_op_c == false)
		tcsetattr(STDIN, TCSANOW, &(info->terminal[ORIGINAL]));
	setting_1_5(info);
	*environ = get_environ(info->env, info);
	*paths = ft_getenv("PATH", info->env, false);
	*paths = ft_strdup(*paths);
	if (*paths == NULL)
		all_free_exit(info, ERR_MALLOC, LINE, FILE);
	if (*paths && (*paths)[0] == ':')
	{
		*paths = re_strjoin(paths, ".", *paths);
		if (*paths == NULL)
			all_free_exit(info, ERR_MALLOC, LINE, FILE);
	}
	else if (*paths && (*paths)[ft_strlen(*paths) - 1] == ':')
	{
		*paths = re_strjoin(paths, *paths, ".");
		if (*paths == NULL)
			all_free_exit(info, ERR_MALLOC, LINE, FILE);
	}
	if ((*paths)[0] != '\0')
		*split = ft_split(*paths, ':');
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
	{
		while ((*split)[++i])
		{
			tmp = check_executable_file_in_bin_dir((*split)[i], command, info);
			if (tmp)
			{
				free((*split)[i]);
				(*split)[i] = tmp;
			}
		}
	}
	(void)paths;
	(void)len;
	return (i);
}
