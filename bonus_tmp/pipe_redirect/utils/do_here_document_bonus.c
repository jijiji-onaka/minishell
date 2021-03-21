/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_here_document_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 14:07:59 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/21 16:51:50 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell_bonus.h"

static void	preparation(int *backup, char **inputs,
					char *stopper, t_minishell *info)
{
	if (write(STDOUT_FILENO, "wait :(", 7) < 7)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (write(STDOUT_FILENO, stopper, ft_strlen(stopper)) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (write(STDOUT_FILENO, ")> ", 3) < 3)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if ((*backup = dup(STDIN_FILENO)) == -1)
		all_free_exit(info, ERR_DUP, __LINE__, __FILE__);
	if (!(*inputs = ft_strdup("\0")))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	g_signal.reading = true;
}

static bool	press_newline(char **inputs, char *stopper,
				int fd, bool expand_flag)
{
	if (ft_strcmp(*inputs, stopper) == 0)
	{
		ptr_free((void**)inputs);
		return (true);
	}
	if (expand_flag)
		change_env_for_here_doc(inputs, &(g_signal.info));
	if (ft_putendl_fd(*inputs, fd) == false)
		all_free_exit(&(g_signal.info), ERR_WRITE, __LINE__, __FILE__);
	if (!(*inputs = re_strdup(inputs, "\0")))
		all_free_exit(&(g_signal.info), ERR_MALLOC, __LINE__, __FILE__);
	if (write(STDOUT_FILENO, "wait :(", 7) < 7)
		all_free_exit(&(g_signal.info), ERR_WRITE, __LINE__, __FILE__);
	if (write(STDOUT_FILENO, stopper, ft_strlen(stopper)) < 0)
		all_free_exit(&(g_signal.info), ERR_WRITE, __LINE__, __FILE__);
	if (write(STDOUT_FILENO, ")> ", 3) < 3)
		all_free_exit(&(g_signal.info), ERR_WRITE, __LINE__, __FILE__);
	return (false);
}

static void	clean_up(int *backup, char **inputs, t_minishell *info)
{
	if (!g_signal.reading)
		if ((dup2(*backup, STDIN_FILENO)) == -1)
		{
			ptr_free((void**)inputs);
			ptr_free((void**)info->ptr_for_free);
			info->ptr_for_free = NULL;
			all_free_exit(info, ERR_DUP2, __LINE__, __FILE__);
		}
	if (ft_close(backup) == false)
	{
		ptr_free((void**)inputs);
		ptr_free((void**)info->ptr_for_free);
		info->ptr_for_free = NULL;
		all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	}
	info->ptr_for_free = NULL;
	ptr_free((void **)inputs);
}

static void	*press_eof(char **inputs, \
				int *backup, t_minishell *info)
{
	ptr_free((void **)inputs);
	clean_up(backup, inputs, info);
	return (NULL);
}

bool		do_here_document(t_minishell *info, int fd, char *stopper,
									bool expand_flag)
{
	char	buf;
	char	*inputs;
	int		backup;
	ssize_t	rc;

	preparation(&backup, &inputs, stopper, info);
	buf = '\0';
	g_signal.sig_sign = 0;
	while (g_signal.reading)
	{
		if ((rc = safe_read(&buf, &inputs, info)) < 0)
			break ;
		ctrl_d_rm(&inputs, info);
		if (rc == 0 && inputs[0] == '\0')
			return (press_eof(&inputs, &backup, info));
		if (buf == '\n' && press_newline(&inputs, stopper, fd, expand_flag))
			break ;
		else if (buf != '\n' && !(inputs = re_strjoinch(&inputs, buf)))
			all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	}
	clean_up(&backup, &inputs, info);
	g_signal.sig_sign = 1;
	if (!g_signal.reading)
		return (reset_prompt(NULL, NULL));
	return (true);
}
