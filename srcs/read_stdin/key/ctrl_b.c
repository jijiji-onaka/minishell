/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 12:17:07 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/13 12:17:52 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*create_new_command(t_string *command, t_minishell *info)
{
	char	*new;
	int		index[3];
	int		len;
	int		insert_index;

	len = ft_strlen(command->str) + ft_strlen(info->key.target);
	new = malloc(len + 1);
	if (new == NULL)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	index[0] = 0;
	index[1] = 0;
	index[2] = 0;
	insert_index = get_command_len_from_pos(info->cursor.cur_pos,
			info->cursor.command_start_pos, info);
	while (index[1] < len)
	{
		if (index[1] != insert_index)
			new[index[1]++] = command->str[index[0]++];
		else
			while (info->key.target[index[2]])
				new[index[1]++] = info->key.target[index[2]++];
	}
	new[index[1]] = '\0';
	return (new);
}

void	paste_selected_str(char *buf, t_string *command, t_minishell *info)
{
	char	*tmp;
	int		original_pos;
	int		i;

	(void)buf;
	if (info->key.target == NULL)
		return ;
	original_pos = get_command_len_from_pos(info->cursor.command_end_pos,
			info->cursor.cur_pos, info);
	tmp = create_new_command(command, info);
	delete_displayed_command(where_err(LINE, FILE), command, info);
	ptr_free((void **)&(command->str));
	dup_pos(info->cursor.cur_pos, info->cursor.command_start_pos);
	dup_pos(info->cursor.command_end_pos, info->cursor.cur_pos);
	command->str = tmp;
	command->len = ft_strlen(tmp);
	display_command(command, info);
	i = -1;
	while (++i < original_pos)
		move_cursor_left(NULL, NULL, info);
}
