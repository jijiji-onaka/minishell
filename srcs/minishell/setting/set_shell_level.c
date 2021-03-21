/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_shell_level.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 01:55:24 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/21 02:29:24 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	get_shlvl(const char *str)
{
	int			i;
	long long	res;
	int			f;

	i = 0;
	res = 0;
	f = 1;
	while (str[i] && (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' ||
			str[i] == '\v' || str[i] == '\f' || str[i] == '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
		f = 44 - str[i++];
	while (ft_isdigit(str[i]))
	{
		if (res > (res * 10 + (str[i] - '0')) / 10)
			return (f == -1 ? (0) : (-1));
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0' && str[i] != ' ' && str[i] != '\t')
		return (0);
	return (res * f);
}

static void	warning_high_shlvl(int *shlvl, int *len)
{
	if (*shlvl == 1000)
		*len = 0;
	else if (*shlvl >= 1000)
	{
		if (write(2, "minishell: warning: shell level (", 33) < 33)
			exit(EXIT_FAILURE);
		if (ft_putnbr_fd(*shlvl, 2) == false)
			exit(EXIT_FAILURE);
		if (write(2, ") too high, resetting to 1\n", 27) < 27)
			exit(EXIT_FAILURE);
		*shlvl = 1;
		*len = 1;
	}
	else if (*shlvl == 0)
	{
		*shlvl = 0;
		*len = 1;
	}
}

static void	fuck_norm(int *current_shlvl, int *len, char *s)
{
	*current_shlvl = get_shlvl(s) + 1;
	*len = ft_numlen(*current_shlvl);
	warning_high_shlvl(current_shlvl, len);
}

void		set_shell_level(void)
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
			fuck_norm(&current_shlvl, &len, environ[i] + j);
			environ[i][j + len] = '\0';
			if (current_shlvl == 0)
				environ[i][j + len - 1] = '0';
			else
				while (current_shlvl != 0)
				{
					environ[i][j + len-- - 1] = current_shlvl % 10 + '0';
					current_shlvl /= 10;
				}
		}
}
