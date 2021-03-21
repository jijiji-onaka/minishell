/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_message.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 02:09:10 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/21 01:56:42 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool			err_no_such_file_or_directory(char *filename, t_minishell *info)
{
	if (write(STDERR_FILENO, "minishell: ", 11) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (ft_putstr_fd(filename, STDERR_FILENO) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (write(STDERR_FILENO, ": No such file or directory\n", 28) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	return (false);
}

static size_t	word_count(char const *s, char c)
{
	size_t		cnt;

	cnt = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s && *s != c)
		{
			cnt++;
			while (*s && *s != c)
				s++;
		}
	}
	return (cnt);
}

bool			err_ambiguous_redirect(char **filename, t_minishell *info)
{
	char	*tmp;
	int		num;

	if (!(tmp = ft_strdup(*filename)))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	change_env_and_quo_and_slash(filename, info);
	num = word_count(*filename, ' ');
	if (num == 1 || ft_strchr(tmp, '$') == NULL)
	{
		ptr_free((void**)&tmp);
		return (true);
	}
	if (write(STDERR_FILENO, "minishell: ", 11) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (ft_putstr_fd(tmp, STDERR_FILENO) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (write(STDERR_FILENO, ": ambiguous redirect\n", 21) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	g_signal.exit_status = EXIT_FAILURE;
	ptr_free((void**)&tmp);
	return (false);
}
