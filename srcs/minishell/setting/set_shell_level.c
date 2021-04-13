/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_shell_level.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 01:55:24 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/10 16:01:09 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	return_num(int flag)
{
	if (flag == -1)
		return (0);
	return (-1);
}

static int	get_shlvl(const char *str)
{
	int			i;
	long long	res;
	int			f;

	i = 0;
	res = 0;
	f = 1;
	while (str[i] && (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
			|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
		f = 44 - str[i++];
	while (ft_isdigit(str[i]))
	{
		if (res > (res * 10 + (str[i] - '0')) / 10)
			return (return_num(f));
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

static void	set_shlvl(char *shlvl_env)
{
	size_t	i;
	int		len;
	int		shlvl;

	i = 0;
	while (shlvl_env[i++] != '=')
		;
	shlvl = get_shlvl(shlvl_env + i) + 1;
	len = ft_numlen(shlvl);
	warning_high_shlvl(&shlvl, &len);
	shlvl_env[i + len] = '\0';
	if (shlvl == 0)
		shlvl_env[i + len - 1] = '0';
	else
	{
		while (shlvl != 0)
		{
			shlvl_env[i + len-- - 1] = shlvl % 10 + '0';
			shlvl /= 10;
		}
	}
}

void	set_shell_level(void)
{
	extern char	**environ;
	size_t		i;
	int			j;
	int			current_shlvl;
	int			len;

	i = -1;
	while (environ[++i])
	{
		if (ft_strncmp(environ[i], "SHLVL", 5) != MATCH)
			continue ;
		set_shlvl(environ[i]);
		return ;
	}
}
