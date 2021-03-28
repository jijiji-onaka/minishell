/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting_for_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 01:01:05 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/28 18:06:52 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	preparation(int *backup, t_string *command,
					char buf[4], t_minishell *info)
{
	if ((*backup = dup(STDIN_FILENO)) == -1)
		all_free_exit(info, ERR_DUP, __LINE__, __FILE__);
	if (!(command->str = ft_strdup("")))
	{
		if (ft_close(backup) == false)
			all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	}
	command->len = 0;
	buf[0] = '\0';
	g_global.reading = true;
	info->history_flag = false;
}

// static void	check_return_value(ssize_t rc, char **command, char buf[4], \
// 			t_minishell *info)
// {
// 	if (rc != 0)
// 	{
// 		if (!(*command = re_strjoin(command, *command, buf)))
// 			all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
// 	}
// 	else if (rc == 0 && (*command)[0] == '\0')
// 		ctrl_d_exit(command, info);
// }

static void	clean_up(int *backup, char **command, t_minishell *info)
{
	if (!g_global.reading)
		if ((dup2(*backup, STDIN_FILENO)) == -1)
		{
			ptr_free((void**)command);
			all_free_exit(info, ERR_DUP2, __LINE__, __FILE__);
		}
	if (ft_close(backup) == false)
	{
		ptr_free((void**)command);
		all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	}
	// printf("{%s}\n", info->ptr_for_free);
	if (info->ptr_for_free)
		ptr_free((void**)&(info->ptr_for_free));
	// printf("{%s}\n", info->ptr_for_free);
}

ssize_t		safe_read1(char buf[4], char **ptr, t_minishell *info)
{
	ssize_t	rc;

	rc = read(STDIN_FILENO, buf, 3);
	if (rc < 0)
	{
		if (ptr)
			ptr_free((void**)ptr);
		if (errno == EBADF)
			return (-1);
		all_free_exit(info, ERR_READ, __LINE__, __FILE__);
	}
	buf[rc] = '\0';
	// printf("[%s]\n", buf);
	return (rc);
}

void		clear_terminal(char *command, t_minishell *info)
{
	ft_putstr_fd(tgetstr("cl", NULL), STDOUT_FILENO);
	put_prompt(info);
	ft_putstr_fd(command, STDOUT_FILENO);
}

void		print_user_pushed_char(t_string *command, char *buf, t_minishell *info)
{
	// puts("======");
	ft_putchar_fd(*buf, STDOUT_FILENO);
	if (!(command->str = re_strjoin(&(command->str), command->str, buf)))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	command->len++;
}

void		move_cursor_left(char *buf, t_string *command, t_minishell *info)
{
	if (command->len == 0)
	{
		// buf[0] = '\0';
		return ;
	}
	--command->len;
	// ft_putstr_fd(info->key.left, STDIN_FILENO);
	ft_putstr_fd(buf, STDIN_FILENO);
	buf[0] = '\0';
	buf[1] = '\0';
	buf[2] = '\0';
	buf[3] = '\0';
}

void		delete_displayed_char(char *buf, t_string *command, t_minishell *info)
{
	if (command->len == 0)
	{
		buf[0] = '\0';
		return ;
	}
	command->str[command->len - 1] = '\0';
	--command->len;
	if (ft_putstr_fd(info->key.left, 0) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (ft_putstr_fd(info->key.save, 0) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (ft_putstr_fd(info->key.clean_right, 0) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	ft_putstr_fd(tgetstr("rc", NULL), 0);
}

// size_t	ft_strlen1(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		printf("{%c}\n", s[i]);
// 		printf("{%d}\n", s[i]);
// 		i++;
// 	}
// 	printf("{%zd}\n", i);
// 	return (i);
// }

bool		is_up_key(char *buf)
{
	return (buf[0] == 27 && buf[1] == 91 && buf[2] == 65);
}

bool		is_down_key(char *buf)
{
	return (buf[0] == 27 && buf[1] == 91 && buf[2] == 66);
}

bool		is_left_key(char *buf)
{
	return (buf[0] == 27 && buf[1] == 91 && buf[2] == 68);
}

void		trace_history_up(char *buf, t_string *command, t_minishell *info)
{
	char	*history_command;
	int		i;

	if (info->command_history == NULL)
		return ;
	i = -1;
	while (++i < command->len)
		if (ft_putstr_fd(info->key.left, 0) == false)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (ft_putstr_fd(info->key.clean_right, 0) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	history_command = ft_strdup(info->command_history->command);
	if (history_command == NULL)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	if (info->command_history->prev)
		info->command_history = info->command_history->prev;
	if (info->history_flag == false)
	{
		info->ptr_for_free = command->str;
		info->history_flag = true;
	}
	else
		ptr_free((void**)&(command->str));
	if (ft_putstr_fd(history_command, STDOUT_FILENO) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	command->str = history_command;
	command->len = ft_strlen(history_command);
}

void		trace_history_down(char *buf, t_string *command, t_minishell *info)
{
	char	*history_command;
	int		i;

	if (info->command_history == NULL || (info->history_flag == false && info->command_history->next == NULL))
		return ;
	i = -1;
	while (++i < command->len)
		if (ft_putstr_fd(info->key.left, 0) == false)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (ft_putstr_fd(info->key.clean_right, 0) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (info->command_history->next)
		history_command = ft_strdup(info->command_history->next->command);
	else
	{
		history_command = info->ptr_for_free;
		info->ptr_for_free = NULL;
		info->history_flag = false;
	}
	if (history_command == NULL)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	if (info->command_history->next)
		info->command_history = info->command_history->next;
	ptr_free((void**)&(command->str));
	if (ft_putstr_fd(history_command, STDOUT_FILENO) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	command->str = history_command;
	command->len = ft_strlen(history_command);
}

void		check_key(char *buf, t_string *command, t_minishell *info)
{
	// printf("[%s]\n", buf);
	// printf("[%d]\n", buf[0]);
	// printf("[%d]\n", buf[1]);
	// printf("[%d]\n", buf[2]);
	// // printf("[%s]\n", buf);
	// printf("q[%d]\n", info->key.left[0]);
	// printf("q[%d]\n", info->key.left[1]);
	// printf("q[%d]\n", info->key.left[2]);
	//  write(1, "abc", 3);
	if (buf[0] == CTRL_D && command->str[0] == '\0')
		ctrl_d_exit(&(command->str), info);
	else if (buf[0] == CTRL_L)
		clear_terminal(command->str, info);
	else if (buf[0] == DELETE_KEY)
		delete_displayed_char(buf, command, info);
	// else if (ft_strlen(buf) == 1)
	// 	print_user_pushed_char(command, buf, info);
	else if (is_up_key(buf))
		trace_history_up(buf, command, info);
	else if (is_down_key(buf))
		trace_history_down(buf, command, info);
	else if (is_left_key(buf))
		move_cursor_left(buf, command, info);
	// write(1, "\033[D", 3);
	// if (ft_strlen(buf) == 1)
	// 	if (!(command->str = re_strjoin(&(command->str), command->str, buf)))
	// 		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	else
		print_user_pushed_char(command, buf, info);
}

char		*waiting_for_input(t_minishell *info)
{
	t_string	command;
	char		buf[4];
	ssize_t		rc;
	int			backup;

	preparation(&backup, &command, buf, info);
	while (g_global.reading)
	{
		rc = safe_read1(buf, &(command.str), info);
		if (rc == -1)
		{
			puts("read error");
			break ;
		}
		ctrl_d_rm(&(command.str), info);
		check_key(buf, &command, info);
		// check_return_value(rc, &command, buf, info);
		if (ft_strchr(buf, '\n') != NULL)
			break ;
	}
	clean_up(&backup, &(command.str), info);
	// all_free_minishell_info(info);
	// free(command.str);
	// tcsetattr(STDIN_FILENO, TCSANOW, &(g_global.terms[ORIGINAL]));
	// exit(0);
	if (!g_global.reading)
		return (reset_prompt(&(command.str), NULL));
	return (command.str);
}

// static void	preparation(int *backup, char **command,
// 					char *buf, t_minishell *info)
// {
// 	if ((*backup = dup(STDIN_FILENO)) == -1)
// 		all_free_exit(info, ERR_DUP, __LINE__, __FILE__);
// 	if (!(*command = ft_strdup("")))
// 	{
// 		if (ft_close(backup) == false)
// 			all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
// 		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
// 	}
// 	*buf = '\0';
// 	g_global.reading = true;
// }

// static void	check_return_value(ssize_t rc, char **command, char buf, \
// 			t_minishell *info)
// {
// 	if (rc != 0)
// 	{
// 		if (!(*command = re_strjoinch(command, buf)))
// 			all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
// 	}
// 	else if (rc == 0 && (*command)[0] == '\0')
// 		ctrl_d_exit(command, info);
// }

// static void	clean_up(int *backup, char **command, t_minishell *info)
// {
// 	if (!g_global.reading)
// 		if ((dup2(*backup, STDIN_FILENO)) == -1)
// 		{
// 			ptr_free((void**)command);
// 			all_free_exit(info, ERR_DUP2, __LINE__, __FILE__);
// 		}
// 	if (ft_close(backup) == false)
// 	{
// 		ptr_free((void**)command);
// 		all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
// 	}
// }

// char		*waiting_for_input(t_minishell *info)
// {
// 	char	*command;
// 	char	buf;
// 	ssize_t	rc;
// 	int		backup;

// 	preparation(&backup, &command, &buf, info);
// 	while (g_global.reading)
// 	{
// 		if ((rc = safe_read(&buf, &command, info)) && buf == '\n')
// 			break ;
// 		ctrl_d_rm(&command, info);
// 		check_return_value(rc, &command, buf, info);
// 	}
// 	clean_up(&backup, &command, info);
// 	if (!g_global.reading)
// 		return (reset_prompt(&command, NULL));
// 	return (command);
// }
