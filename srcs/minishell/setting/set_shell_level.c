/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_shell_level.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 01:55:24 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/27 01:56:30 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	set_shell_level(void)
{
	extern char	**environ;
	size_t		i;
	int			j;
	int			current_shlvl;
	int			len;

	i = -1;
	while (environ[++i])
		if (environ[i][0] == 'S' && environ[i][1] == 'H' &&
			ft_strncmp(environ[i], "SHLVL", 5) == 0)
		{
			j = 0;
			while (environ[i][j++] != '=')
				;
			current_shlvl = ft_atoi(environ[i] + j) + 1;
			len = ft_numlen(current_shlvl);
			environ[i][j + len] = '\0';
			while (current_shlvl != 0)
			{
				environ[i][j + len - 1] = current_shlvl % 10 + '0';
				current_shlvl /= 10;
				len--;
			}
		}
}
