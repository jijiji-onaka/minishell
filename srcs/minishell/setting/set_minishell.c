/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_minishell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 16:01:47 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/02 22:48:30 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_history	*initial_make_struct_history(int fd, char *line, t_history *prev,
						t_minishell *info)
{
	t_history	*new;

	new = malloc(sizeof(t_history));
	if (new == NULL)
	{
		close(fd);
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	}
	new->command = line;
	new->next = NULL;
	new->prev = prev;
	return (new);
}

void	get_command_history(int fd, t_minishell *info)
{
	char		*line;
	int			ret;
	t_history	*history;
	t_history	*next;

	line = NULL;
	ret = get_next_line(fd, &line);
	history = initial_make_struct_history(fd, line, NULL, info);
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		if (ret == 0 || line[0] == '\0')
		{
			ptr_free((void**)&line);
			if (ret == 0)
				break ;
			continue ;
		}
		next = initial_make_struct_history(fd, line, history, info);
		history->next = next;
		history = next;
	}
	info->command_history = history;
	info->command_history_begin = history;
}

void	set_command_history(t_minishell *info)
{
	int	fd;

	fd = open(info->history_path, O_RDONLY);
	if (fd == -1)
	{
		info->command_history = NULL;
		info->command_history_begin = NULL;
		return ;
	}
	get_command_history(fd, info);
	return ;
}

void	update_command_history_file(t_minishell *info, t_history *history)
{
	int	fd;

	if (history == NULL)
		return ;
	fd = open(info->history_path, O_CREAT | O_RDWR, 0644);
	if (fd == -1)
		all_free_exit(info, ERR_OPEN, __LINE__, __FILE__);
	while (history->prev)
		history = history->prev;
	while (history)
	{
		if (ft_putstr_fd(history->command, fd) == false)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
		if (write(fd, "\n", 1) < 1)
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
		history = history->next;
	}
}

void	set_minishell(t_minishell *info)
{
	info->cmd_lst = NULL;
	info->cmd_lst_num = 0;
	info->exit_too_arg = 0;
	info->unset_pwd_flag = false;
	info->unset_oldpwd_flag = false;
	info->minishell_op_no_edit = false;
	info->env = NULL;
	info->history_path = "./.minishell_history";
	info->command_history = NULL;
	info->ptr_for_free = NULL;
	info->ptr_for_free_2 = NULL;
	info->ptr_2d_for_free = NULL;
	info->key.target = NULL;
	set_shell_level();
	set_env(info);
	set_command_history(info);
	if (!(info->current_dir_path = getcwd(NULL, 0)))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	if (!(info->oldpwd_path = ft_strdup(ft_getenv("OLDPWD", info->env, false))))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
}
