/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_normal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:53:58 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/29 21:28:40 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	edit_displayed_char(char *buf, t_string *command, t_minishell *info)
{
	char	*new;
	size_t	i;
	size_t	j;

	new = malloc(sizeof(char) * (ft_strlen(command->str) + 2));
	if (new == NULL)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	i = 0;
	j = 0;
	new[command->len] = buf[0];
	while (command->str[i])
	{
		if (j != command->len)
		{
			new[j] = command->str[i];
			i++;
		}
		j++;
	}
	new[i + 1] = '\0';
	free(command->str);
	command->str = new;
}

void		print_user_pushed_char(char *buf, t_string *command,
									t_minishell *info)
{
	if (info->key.save_command_len == command->len)
	{
		ft_putchar_fd(*buf, STDOUT_FILENO);
		if (!(command->str = re_strjoin(&(command->str), command->str, buf)))
			all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
		command->len++;
		info->key.save_command_len = command->len;
		return ;
	}
	if (ft_putstr_fd(info->key.save, STDIN_FILENO) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (ft_putstr_fd(info->key.clean_right, STDIN_FILENO) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	edit_displayed_char(buf, command, info);
	ft_putstr_fd(command->str + command->len, STDOUT_FILENO);
	ft_putstr_fd(info->key.reset, STDIN_FILENO);
	ft_putstr_fd(buf, STDOUT_FILENO);
	command->len++;
}

void		pushed_newline(char *buf, t_string *command, t_minishell *info)
{
	if (write(STDOUT_FILENO, "\n", 1) < 1)
	{
		ptr_free((void**)&(command->str));
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	}
	if (command->str[0] == '\0')
		ptr_free((void**)&(command->str));
}
