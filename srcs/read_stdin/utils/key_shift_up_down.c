/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_shift_up_down.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 05:58:56 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/06 10:01:26 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void		get_start_and_len(int *start, int *cut_len, int *original_pos,
								t_minishell *info)
{
	int	length;

	length = get_command_len_from_pos(info->cursor.select_pos,
				info->cursor.cur_pos, info);
	if (length < 0)
	{
		*cut_len = -length;
		*start = get_command_len_from_pos(info->cursor.select_pos,
					info->cursor.command_start_pos, info);
		if (original_pos)
			*original_pos = get_command_len_from_pos(info->cursor.select_pos,
								info->cursor.command_start_pos, info);
	}
	else
	{
		*cut_len = length;
		*start = get_command_len_from_pos(info->cursor.cur_pos,
					info->cursor.command_start_pos, info);
		if (original_pos)
			*original_pos = get_command_len_from_pos(info->cursor.cur_pos,
								info->cursor.command_start_pos, info);
	}
}

// static int	get_start_and_len(int *start, int *cut_len, int *original_pos,
// 								t_minishell *info)
// {
// 	int	length;

// 	length = get_command_len_from_pos(info->cursor.select_pos,
// 				info->cursor.cur_pos, info);
// 	if (length < 0)
// 	{
// 		*cut_len = -length;
// 		*start = get_command_len_from_pos(info->cursor.select_pos,
// 					info->cursor.command_start_pos, info);
// 		if (original_pos)
// 			*original_pos = get_command_len_from_pos(info->cursor.select_pos,
// 								info->cursor.command_start_pos, info);
// 		return (SELECT_LEFT);
// 	}
// 	else
// 	{
// 		*cut_len = length;
// 		*start = get_command_len_from_pos(info->cursor.cur_pos,
// 					info->cursor.command_start_pos, info);
// 		if (original_pos)
// 			*original_pos = get_command_len_from_pos(info->cursor.cur_pos,
// 								info->cursor.command_start_pos, info);
// 		return (SELECT_RIGHT);
// 	}
// }

void		copy_command(char *buf, t_string *command, t_minishell *info)
{
	int		start;
	int		copy_len;

	(void)buf;
	info->key.shift_ctrl_lr_flag = false;
	// copy_len = get_command_len_from_pos(info->cursor.select_pos,
	// 				info->cursor.cur_pos, info);
	get_start_and_len(&start, &copy_len, NULL, info);
	// printf("[[[[[[[%d]]]\n", start);
	// printf("[[[[[[[%d]]]\n", copy_len);
	free(info->key.target);
	if (copy_len == 0)
		info->key.target = ft_substr(command->str, 0, -1);
	else
		info->key.target = ft_substr(command->str, start, copy_len);
	if (info->key.target == NULL)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	// printf("[[[[[[[%s]]]\n", info->key.target);
}

static char	*create_new_command(t_string *command, int start, int len,
									t_minishell *info)
{
	int		old_i;
	int		new_i;
	int		end;
	char	*new;

	old_i = 0;
	new_i = 0;
	end = len + start;
	if (len == 0)
		new = ft_strdup("");
	else
		new = malloc(ft_strlen(command->str) + 1);
	if (new == NULL)
		all_free_exit(info, ERR_MALLOC, LINE, FILE);
	if (len == 0)
		return (new);
	else
		while (command->str[old_i])
		{
			if (!(start <= old_i && old_i < end))
				new[new_i++] = command->str[old_i];
			old_i++;
		}
	new[new_i] = '\0';
	return (new);
}


static void	move_original_cursor_pos(int move_len, t_minishell *info)
{
	int		i;

	i = 0;
	move_specified_position(info->cursor.command_start_pos[Y],
		info->cursor.command_start_pos[X], where_err(LINE, FILE), info);
	dup_pos(info->cursor.cur_pos, info->cursor.command_start_pos);
	while (i < move_len)
	{
		move_cursor_right(NULL, NULL, info);
		i++;
	}
}

void		cut_command(char *buf, t_string *command, t_minishell *info)
{
	int		start;
	int		cut_len;
	char	*tmp;
	int		original_pos;

	(void)buf;
	info->key.shift_ctrl_lr_flag = false;
	get_start_and_len(&start, &cut_len, &original_pos, info);
	free(info->key.target);
	if (cut_len == 0)
		info->key.target = ft_substr(command->str, 0, -1);
	else
		info->key.target = ft_substr(command->str, start, cut_len);
	if (info->key.target == NULL)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	tmp = create_new_command(command, start, cut_len, info);
	delete_displayed_command(where_err(LINE, FILE), command, info);
	ptr_free((void**)&(command->str));
	command->str = tmp;
	command->len = ft_strlen(tmp);
	dup_pos(info->cursor.cur_pos, info->cursor.command_start_pos);
	dup_pos(info->cursor.command_end_pos, info->cursor.cur_pos);
	display_command(command, info);
	move_original_cursor_pos(original_pos, info);
}
