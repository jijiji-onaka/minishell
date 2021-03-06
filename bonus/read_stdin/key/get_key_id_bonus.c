/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_key_id_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 10:08:47 by tjinichi          #+#    #+#             */
/*   Updated: 2021/05/25 01:39:18 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bonus_includes/minishell_bonus.h"

static int	key_multi_byte(t_minishell *info, bool home_or_end)
{
	if (home_or_end == HOME)
		info->key.multi_byte_flag = true;
	else
		info->key.multi_byte_flag_2 = true;
	return (TO_BE_CONTINUE);
}

static int	warning_multibyte(char *buf, t_string *command, t_minishell *info)
{
	putstr_fd("\nminishell: Only single-byte characters are supported.\n",
		STDERR, where_err(LINE, FILE), info);
	command->str[0] = '\0';
	buf[0] = '\n';
	return (KEY_NEWLINE);
}

/*
** KEY_TAB and NOTHING_KEY have the same value
*/

static int	get_key_id_3(char *buf, t_string *command, t_minishell *info)
{
	if (info->key.multi_byte_flag == true)
	{
		if (buf[0] == 59 && buf[1] == 53 && buf[2] == 68)
			return (KEY_CTRL_LEFT);
		else if (buf[0] == 59 && buf[1] == 53 && buf[2] == 67)
			return (KEY_CTRL_RIGHT);
		else if (buf[0] == 59 && buf[1] == 50 && buf[2] == 68)
			return (KEY_SHIFT_LEFT);
		else if (buf[0] == 59 && buf[1] == 50 && buf[2] == 67)
			return (KEY_SHIFT_RIGHT);
		else if (buf[0] == 59 && buf[1] == 50 && buf[2] == 65)
			return (KEY_SHIFT_UP);
		else if (buf[0] == 59 && buf[1] == 50 && buf[2] == 66)
			return (KEY_SHIFT_DOWN);
		else if (buf[0] == 126 && buf[1] == '\0')
			return (KEY_HOME);
	}
	else if (info->key.multi_byte_flag_2 == true
		&& buf[0] == 126 && buf[1] == '\0')
		return (KEY_END);
	else if (ft_isprint(buf[0]))
		return (NORMAL_CHAR);
	else if ((unsigned char)buf[0] > 127)
		return (warning_multibyte(buf, command, info));
	return (NOTHING_KEY);
}

static int	get_key_id_2(char *buf, t_minishell *info)
{
	if (buf[0] == 2)
		return (CTRL_B);
	else if (buf[0] == 16)
		return (CTRL_P);
	else if (buf[0] == 14)
		return (CTRL_N);
	else if (info->minishell_op_no_edit == false && buf[0] == 9)
		return (KEY_TAB);
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 65)
		return (KEY_UP);
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 66)
		return (KEY_DOWN);
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 67)
		return (KEY_RIGHT);
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 68)
		return (KEY_LEFT);
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 49)
		return (key_multi_byte(info, HOME));
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 52)
		return (key_multi_byte(info, END));
	return (-42);
}

int	get_key_id(char *buf, t_string *command, t_minishell *info)
{
	int	key;

	if (buf[0] == 4)
		return (CTRL_D);
	else if (buf[0] == 12)
		return (CTRL_L);
	else if (buf[0] == 127 || buf[0] == 8)
		return (KEY_DELETE);
	else if (buf[0] == 10)
		return (KEY_NEWLINE);
	key = get_key_id_2(buf, info);
	if (key != -42)
		return (key);
	key = get_key_id_3(buf, command, info);
	return (key);
}
