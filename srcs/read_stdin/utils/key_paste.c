/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_paste.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 07:10:07 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/04 03:01:09 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	create_new_command(t_string *command, t_minishell *info)
{
	char	*new;
	size_t	src_i;
	size_t	new_i;
	size_t	paste_i;

	new = malloc(ft_strlen(command->str) +
		ft_strlen(info->key.target) + 1);
	if (new == NULL)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	src_i = 0;
	new_i = 0;
	paste_i = 0;
	while (command->str[src_i] || info->key.target[paste_i])
	{
		if (src_i != command->len || paste_i != 0)
			new[new_i++] = command->str[src_i++];
		else
			while (info->key.target[paste_i])
				new[new_i++] = info->key.target[paste_i++];
	}
	new[new_i] = '\0';
	free(command->str);
	command->str = new;
	command->len = new_i;
	info->key.save_command_len = new_i;
}

void		paste(char *buf, t_string *command, t_minishell *info)
{
	size_t	len;

	if (info->key.target == NULL)
		return ;
	len = command->len;
	// int i = -1;
	// printf("[%s]\n", command->str);
	// printf("[%s]\n", info->key.target);
	delete_displayed_command(len, info->key.left, info->key.clean_right);
	// while (++i < info->key.target_end - info->key.target_start - 1)
	// 	if (ft_putstr_fd(info->key.right, STDIN) == false)
	// 		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	create_new_command(command, info);
	if (ft_putstr_fd(command->str, STDIN) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	// if (command->len == info->key.save_command_len)
	// 	puts("+++++++");
}
