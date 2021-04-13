/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_message_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 02:09:10 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/13 14:57:18 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bonus_includes/minishell_bonus.h"

bool	err_no_such_file_or_directory(char *filename, t_minishell *info)
{
	if (write(STDERR, "minishell: ", 11) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (ft_putstr_fd(filename, STDERR) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (write(STDERR, ": No such file or directory\n", 28) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	return (false);
}

bool	err_ambiguous_redirect(char **filename, t_minishell *info)
{
	char	*tmp;
	int		num;

	tmp = ft_strdup(*filename);
	if (tmp == NULL)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	change_env_and_quo_and_slash(filename, info);
	num = word_count(*filename, ' ');
	if (num == 1 || ft_strchr(tmp, '$') == NULL)
	{
		ptr_free((void **)&tmp);
		return (true);
	}
	if (write(STDERR, "minishell: ", 11) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (ft_putstr_fd(tmp, STDERR) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (write(STDERR, ": ambiguous redirect\n", 21) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	g_global.exit_status = EXIT_FAILURE;
	ptr_free((void **)&tmp);
	return (false);
}
