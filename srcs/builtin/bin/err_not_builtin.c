/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_not_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 14:23:17 by tjinichi          #+#    #+#             */
/*   Updated: 2021/05/13 00:50:04 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// static char	*decide_error_message_2(char *command, t_minishell *info
// 			, bool is_path, bool is_sla_in_cmd)
// {
// 	int			fd;

// 	(void)is_path;
// 	// if (is_path)
// 	// {
// 		fd = open(command, O_WRONLY);
// 		if (errno == ENOENT)
// 			g_global.exit_status = CMD_NOT_FOUND;
// 		else
// 			g_global.exit_status = 126;
// 		if (fd != -1 && close(fd) == -1)
// 			all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
// 		// if (errno == ENOENT)
// 		// 	return (NULL);
// 		// else
// 			return (strerror(errno));
// 	// }
// 	struct stat ff;

// 	if (lstat(command, &ff) == 0 && is_sla_in_cmd)
// 	{
// 		if (errno == EACCES)
// 		{
// 			g_global.exit_status = 126;
// 			return (strerror(errno));
// 		}
// 	}
// 	errno = 0;
// 	g_global.exit_status = CMD_NOT_FOUND;
// 	return (NULL);
// }

// static char	*decide_error_message_3(char *command, t_minishell *info
// 			, bool is_path, bool is_sla_in_cmd)
// {
// 	int			fd;

// 	(void)is_sla_in_cmd;
// 	if (is_path)
// 	{
// 		fd = open(command, O_WRONLY);
// 		if (errno == ENOENT)
// 			g_global.exit_status = CMD_NOT_FOUND;
// 		else
// 			g_global.exit_status = 126;
// 		if (fd != -1 && close(fd) == -1)
// 			all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
// 		if (errno == ENOENT || errno == EACCES)
// 			return (NULL);
// 		else
// 			return (strerror(errno));
// 	}
// 	struct stat ff;

// 	if (lstat(command, &ff) == 0 && is_sla_in_cmd)
// 	{
// 		if (errno == EACCES)
// 		{
// 			g_global.exit_status = 126;
// 			return (strerror(errno));
// 		}
// 	}
// 	errno = 0;
// 	g_global.exit_status = CMD_NOT_FOUND;
// 	return (NULL);
// }

// static char	*decide_error_message(char *command, t_minishell *info
// 			, bool is_path, bool is_sla_in_cmd)
// {
// 	struct stat	st;
// 	int			fd;

// 	if (is_sla_in_cmd == true)
// 		return (decide_error_message_2(command, info, is_path, is_sla_in_cmd));
// 	if (is_path == true)
// 		return (decide_error_message_3(command, info, is_path, is_sla_in_cmd));
// 	// printf("command [%s]\n", command);
// 	// printf("is_path [%d]\n", is_path);
// 	// printf("is_sla_in_cmd [%d]\n", is_sla_in_cmd);
// 	lstat(command, &st);
// 	if (S_ISREG(st.st_mode) && ((S_IXUSR | S_IXGRP | S_IXOTH) & st.st_mode))
// 	{
// 		if (errno == EACCES && !(S_IRUSR & st.st_mode))
// 		{
// 			g_global.exit_status = 126;
// 			return (strerror(errno));
// 		}
// 		exit(EXIT_SUCCESS);
// 	}
// 	fd = open(command, O_WRONLY);
// 	if (errno == ENOENT || errno == EACCES)
// 		g_global.exit_status = 127;
// 	else
// 		g_global.exit_status = 126;
// 	if (fd != -1 && close(fd) == -1)
// 		all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
// 	if (errno == EISDIR)
// 		return ("is a directory");
// 	if (errno == ENOENT || errno == EACCES)
// 	{
// 		errno = ENOENT;
// 		return (NULL);
// 	}
// 	else
// 		return (strerror(errno));
// 	// return (strerror(errno));
// }

bool	search_files(char *dir_name, char *file_name, t_minishell *info)
{
	DIR				*dp;
	struct dirent	*dirp;

	if (safe_opendir(&dp, dir_name, info) == false)
		return (false);
	while (1)
	{
		if (safe_readdir(&dirp, dp, info) == false)
			break ;
		if (dirp->d_name[0] == '.')
			continue ;
		// printf("[%s]\n", dirp->d_name);
		if (equal(ft_strcmp(dirp->d_name, file_name)))
		{
			safe_closedir(&dp, info);
			return (true);
		}
	}
	safe_closedir(&dp, info);
	return (false);
}

// normal
static char	*get_error_message_3(char *command, char *path, t_minishell *info)
{
	char	*res;
	int		fd;
	char	*is_sla;

	// puts("3333333");
	(void)path;
	// 	return ;
	if (ENOEXEC == errno)
		errno = EACCES;
	// perror("");
	is_sla = ft_strchr(command, '/');
	fd = open(command, O_WRONLY);
	if (is_sla == NULL || errno == ENOENT)
	// if (errno == ENOENT || ((errno == ENOEXEC || errno == EACCES) && is_sla == NULL))
	// if (errno == ENOENT)
		g_global.exit_status = CMD_NOT_FOUND;
	else
		g_global.exit_status = 126;
	if (fd != -1 && close(fd) == -1)
		all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	res = ft_str3join("minishell: ", command, ": ");
	// if (errno == EACCES)
	// 	res = re_strjoin(&res, res, "command not found");
	// if (errno == EACCES)
	// 	res = re_strjoin(&res, res, "command not found");
	if (is_sla == NULL)
	// if (is_sla == NULL)
	// {
	// 	if (errno == ENOENT || errno == EACCES || errno == ENOEXEC)
			res = re_strjoin(&res, res, "command not found");
		// else if (errno == EACCES)
		// 	res = re_strjoin(&res, res, "command not found");
		// else
		// 	res = re_strjoin(&res, res, strerror(errno));
	// }
	else
		res = re_strjoin(&res, res, strerror(errno));
	// exit(2);
	return (res);
}

// Path doesn't exist
static char	*get_error_message_2(char *command, char *path, t_minishell *info)
{
	char	*res;
	int		fd;

	// puts("2222222");
	(void)path;
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

// If the last directory in the path exists
static char	*get_error_message_1(char *command, char *path, t_minishell *info)
{
	char	*res;
	int		fd;
	char	*slash;

		// puts("111111");
	slash = ft_strchr(command, '/');
	(void)path;
	if ((slash == NULL && search_files(".", command, info) == true) || errno == ENOEXEC)
	{
		if (slash == NULL && search_files(".", command, info) == true && errno != ENOEXEC)
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
		// if (res == NULL)
		// 	all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
		// return (res);
	}
	fd = open(command, O_WRONLY);
	if (errno == ENOENT)
		g_global.exit_status = CMD_NOT_FOUND;
	else
		g_global.exit_status = 126;
	if (fd != -1 && close(fd) == -1)
		all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	if (errno == EISDIR)
		return ("is a directory");
	res = ft_str3join("minishell: ", command, ": ");
	if (res == NULL)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	res = re_strjoin(&res, res, strerror(errno));
	return (res);
}

bool	is_cwd_in_path(char *path, t_minishell *info)
{
	char	**split;
	int		i;
	bool	ret;

	split = ft_split(path, ':');
	if (split == NULL)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	i = -1;
	ret = false;
	while (split[++i])
	{
		if (split[i][0] == '.')
			ret = true;
	}
	ptr_2d_free((void ***)&split, i);
	return (ret);
}

void	not_builtin(char *command, t_minishell *info, char *path)
{
	(void)command;
	(void)info;
	// char	*tmp;
	char	*errno_message;
	// bool	is_path;
	// bool	is_sla_in_cmd;
	// // char	*path;
	struct stat	st;
	// char	**path_split;

	// puts("11111111111111");
	// if (path == NULL)
	// 	path_split = NULL;
	// else
	// 	path_split = ft_split(path, ':');
	if (ENOEXEC == errno)
	{
		// if (ft_strrchr(command, '/') != NULL)
		// 	command = ft_strrchr(command, '/') + 1;
		lstat(command, &st);
		// if (S_ISREG(st.st_mode) && ((S_IXUSR | S_IXGRP | S_IXOTH) & st.st_mode))
		// {
			if (((S_IRUSR & S_IREAD & st.st_mode) && (command[0] == '.' && command[1] == '/')))
			{
				return ;
				g_global.exit_status = 126;
			}
		// }
	}
	// printf("[%s]\n", path);

	// if (ENOEXEC == errno)
	// 	return ;
	if (path != NULL && path[0] != '\0')
	{
		// printf("[%s]\n", command);
		// printf("[%s]\n", path);

		// tmp = ft_strrchr(path, ':');
		// if (tmp != NULL)
		// {
		// 	// if (*(tmp + 1) == '\0')
		// 	// 	*(path + (ft_strchr(path, ':') - path)) = '\0';
		// 	// else
		// 		path = tmp + 1;
		// }
		// printf("[%s]\n", path);
		// if (path[0] == '\0')
		// 	errno_message = get_error_message_2(command, path, info);
		if (is_cwd_in_path(path, info) == true)
			errno_message = get_error_message_1(command, path, info);
		else
			errno_message = get_error_message_3(command, path, info);
	}
	else
		errno_message = get_error_message_2(command, path, info);
	// printf("errno_message : [%s]\n", errno_message);
	// exit(1);




	// int i = 0;
	// while (split[i])
	// {
	// 	printf("split[i] : %s\n", split[i]);
	// 	i++;
	// }
	// if (split == NULL || lstat(split[0], &st) != 0)
	// // path = ft_getenv("PATH", info->env, false);
	// // printf("[%s]\n", path);
	// // if (path == NULL || path[0] == '\0' || )
	// 	is_path = false;
	// else
	// 	is_path = true;
	// if (ft_strchr(command, '/') == NULL)
	// 	is_sla_in_cmd = false;
	// else
	// 	is_sla_in_cmd = true;
	// printf("is_path : %d\n", is_path);
	// printf("is_sla_in_cmd : %d\n", is_sla_in_cmd);
	// errno_message = decide_error_message(command, info, is_path, is_sla_in_cmd);
	// if (errno_message == NULL)
	// 	errno_message = "command not found";
	// if (write(STDERR, "minishell: ", 11) < 0)
	// 	all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	// if (errno == EACCES)
	// {
	// 	if (write(STDERR, "./", 2) < 0)
	// 		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	// 	errno_message = strerror(EACCES);
	// }
	// if (write(STDERR, command, ft_strlen(command)) < 0)
	// 	all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	// if (write(STDERR, ": ", 2) < 0)
	// 	all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	// printf("[%s]\n", errno_message);
	// fprintf(stderr, "[%s]\n", errno_message);
	write(2, errno_message, ft_strlen(errno_message));
	write(2, "\n", 1);
	free(errno_message);

	// if (ft_putendl_fd(errno_message, STDERR) == false)
	// 	all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	// printf("[%s]\n", errno_message);
}
