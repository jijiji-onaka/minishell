/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_copy_cut.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 05:58:56 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/03 23:25:08 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void		copy(char *buf, t_string *command, t_minishell *info)
{
	char	*target;

	if (info->key.target_start == -1 || info->key.target_end == -1)
		target = ft_substr(command->str, 0, -1);
	else
		target = ft_substr(command->str, info->key.target_start,
			info->key.target_end - info->key.target_start);
	if (target == NULL)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	free(info->key.target);
	info->key.target = target;
}

static void	create_new_command(t_string *command, t_minishell *info)
{
	size_t	old_i;
	size_t	new_i;

	old_i = 0;
	new_i = 0;
	if (info->key.target_start == -1 || info->key.target_end == -1)
		;
	else
		while (command->str[old_i])
		{
			if (info->key.target_start <= old_i && old_i < info->key.target_end)
				;
			else
				command->str[new_i++] = command->str[old_i];
			old_i++;
		}
	command->str[new_i] = '\0';
	command->len = new_i;
	info->key.save_command_len = new_i;
}

void		cut(char *buf, t_string *command, t_minishell *info)
{
	char	*target;

	if (info->key.target_start == -1 || info->key.target_end == -1)
		target = ft_substr(command->str, 0, -1);
	else
		target = ft_substr(command->str, info->key.target_start,
			info->key.target_end - info->key.target_start);
	if (target == NULL)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	free(info->key.target);
	info->key.target = target;
	move_direction(info->key.save_command_len - command->len,
		info->key.right, info);
	delete_displayed_command(info->key.save_command_len, info->key.left,
		info->key.clean_right);
	create_new_command(command, info);
	if (ft_putstr_fd(command->str, STDOUT_FILENO) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	info->key.target_start = -1;
	info->key.target_end = -1;
}
