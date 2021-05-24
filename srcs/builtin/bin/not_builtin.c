/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 14:23:17 by tjinichi          #+#    #+#             */
/*   Updated: 2021/05/16 16:37:34 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
** normal
*/
static char	*get_error_message_3(char *command, t_minishell *info)
{
	char	*res;
	int		fd;
	char	*is_sla;

	if (ENOEXEC == errno)
		errno = EACCES;
	is_sla = ft_strchr(command, '/');
	fd = open(command, O_WRONLY);
	if (is_sla == NULL || errno == ENOENT)
		g_global.exit_status = CMD_NOT_FOUND;
	else
		g_global.exit_status = 126;
	if (fd != -1 && close(fd) == -1)
		all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	res = ft_str3join("minishell: ", command, ": ");
	if (is_sla == NULL)
		res = re_strjoin(&res, res, "command not found");
	else if (errno == EISDIR)
		res = re_strjoin(&res, res, "is a directory");
	else
		res = re_strjoin(&res, res, strerror(errno));
	return (res);
}

/*
** Path doesn't exist or
*/
static char	*get_error_message_2(char *command, t_minishell *info)
{
	char	*res;
	int		fd;

	fd = open(command, O_WRONLY);
	if (errno == ENOENT)
		g_global.exit_status = CMD_NOT_FOUND;
	else
		g_global.exit_status = 126;
	if (fd != -1 && close(fd) == -1)
		all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	if (errno == EACCES)
	{
		g_global.exit_status = 126;
		res = ft_str3join("minishell: ./", command, ": ");
		if (res == NULL)
			all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
		res = re_strjoin(&res, res, strerror(errno));
	}
	else
	{
		res = ft_str3join("minishell: ", command, ": ");
		res = re_strjoin(&res, res, strerror(errno));
	}
	return (res);
}

/*
** If the last directory in the path exists
*/
static char	*get_error_message_1(char *command, t_minishell *info)
{
	char	*res;

	if (errno != ENOEXEC)
	{
		g_global.exit_status = 126;
		res = ft_str3join("minishell: ./", command, ": ");
		if (res == NULL)
			all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
		res = re_strjoin(&res, res, strerror(errno));
	}
	else
	{
		g_global.exit_status = 127;
		res = ft_str3join("minishell: ", command, ": command not found");
	}
	if (res == NULL)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	return (res);
}

void	not_builtin(char *command, t_minishell *info, char *path)
{
	char		*errno_message;
	struct stat	st;

	if (ENOEXEC == errno)
		if (lstat(command, &st) != -1 && ((S_IRUSR & S_IREAD & st.st_mode)
				&& (command[0] == '.' && command[1] == '/')))
			return ;
	if (path != NULL && path[0] != '\0')
	{
		if (is_cwd_in_path(path, info) == true)
			errno_message = get_error_message_1(command, info);
		else
			errno_message = get_error_message_3(command, info);
	}
	else
		errno_message = get_error_message_2(command, info);
	write(STDERR, errno_message, ft_strlen(errno_message));
	write(STDERR, "\n", 1);
	free(errno_message);
}
