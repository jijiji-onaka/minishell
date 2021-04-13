/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 00:04:05 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/04 03:01:19 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	put_newline(t_minishell *info)
{
	if (write(1, "\n", 1) == -1)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	return ;
}

static void	putstr_space(char **s, t_minishell *info, char *next)
{
	if (write(STDOUT, *s, ft_strlen(*s)) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (next != NULL)
		if (write(STDOUT, " ", 1) < 0)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
}

static int	option_n_flag(char **args, bool *flag)
{
	int		i;
	int		j;

	i = 1;
	while (args[i])
	{
		if (ft_strncmp(args[i], "-", 1) == 0)
		{
			if (ft_strncmp(args[i], "-e", 2) == 0
				|| ft_strncmp(args[i], "-E", 2) == 0)
				return (-1);
			if (ft_strncmp(args[i], "-n", 2) != 0)
				return (i);
			j = 0;
			while ((args[i] + 2)[j])
				if ((args[i] + 2)[j++] != 'n')
					return (i);
			*flag = true;
		}
		else
			return (i);
		i++;
	}
	return (i);
}

void	exec_echo(t_minishell *info, t_cmdlst *cmd)
{
	int			i;
	char		**args;
	bool		n_flag;

	args = cmd->arg;
	g_global.exit_status = 0;
	n_flag = false;
	if (args[1] == NULL)
		return (put_newline(info));
	i = option_n_flag(args, &n_flag);
	if (i == -1)
		return (error_mandatory(ERR_ECHO, 21, info));
	if (args[i] == NULL)
		return ;
	while (args[i])
	{
		putstr_space(&(args[i]), info, args[i + 1]);
		if (args[i + 1] == NULL && n_flag == 0)
			put_newline(info);
		i++;
	}
}
