/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_del_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:51:59 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/29 21:33:49 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void		clear_terminal(char *buf, t_string *command, t_minishell *info)
{
	(void)buf;
	ft_putstr_fd(info->key.clean, STDOUT_FILENO);
	put_prompt(info);
	ft_putstr_fd(command->str, STDOUT_FILENO);
}

static void	create_new_command(t_string *command, t_minishell *info)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*str;

	i = 0;
	j = 0;
	str = command->str;
	len = command->len;
	while (str[i])
	{
		if (i != len)
			str[j++] = str[i];
		i++;
	}
	command->str[j] = '\0';
}

void		delete_displayed_char(char *buf, t_string *command,
					t_minishell *info)
{
	if (command->len == 0)
	{
		buf[0] = '\0';
		return ;
	}
	if (ft_putstr_fd(info->key.left, STDIN_FILENO) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (ft_putstr_fd(info->key.save, STDIN_FILENO) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (ft_putstr_fd(info->key.clean_right, STDIN_FILENO) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	ft_putstr_fd(command->str + command->len, 1);
	--command->len;
	create_new_command(command, info);
	ft_putstr_fd(info->key.reset, STDIN_FILENO);
}

bool		delete_displayed_command(size_t len, char *left, char *clean_right)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (ft_putstr_fd(left, STDIN_FILENO) == false)
			return (false);
		i++;
	}
	if (ft_putstr_fd(clean_right, STDIN_FILENO) == false)
		return (false);
	return (true);
}
