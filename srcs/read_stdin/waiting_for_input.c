/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting_for_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 01:01:05 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 17:46:40 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** freeしてfalseを返すだけの関数。normのため分けた
*/

static char	*newline_only(char **command)
{
	ptr_free((void **)command);
	return (NULL);
}

/*
** readの返り値によって1の時はどんどんコマンドに繋げていって
** それ以外はCtrl + Dを押した時の挙動で(*command)[0] == '\0'はpwd[ctrl+D]が押された時に
** exitするのを防いでいる
*/

static void	check_return_value(ssize_t rc, char **command, char buf, \
			t_minishell_info *info)
{
	if (rc != 0)
	{
		if (!(*command = re_strjoinch(command, buf)))
			all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	}
	else if (rc == 0 && (*command)[0] == '\0')
		ctrl_d_exit(command, info);
}

/*
** 1回目はelse ifの方に入る
** buf[1]に'or"が入っていたら"pwd"->pwdになるので"を取り除いている
** 'or"が奇数回押された時はbuf[1]に入ったままwhileを抜けてwait_quotation関数に繋がる
*/

static bool	check_quotation(char **command, char buf[2])
{
	if (buf[1] == buf[0] && buf[0] != '\0')
	{
		rm_chr_in_str(command, buf[1]);
		buf[1] = '\0';
		return (true);
	}
	else if (buf[0] == '\'' || buf[0] == '\"')
		buf[1] = buf[0];
	return (false);
}

/*
** 入力待ちをする関数
** (write(0, "\033[0K", 4);はCtrl + Dを押した時に^Dみたいなのが出るのを防いでいる)
** 返り値boolじゃなくてもいいかも
*/

char		*waiting_for_input(t_minishell_info *info)
{
	char	*command;
	char	buf[2];
	ssize_t	rc;

	if (!(command = ft_strdup("")))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	buf[0] = '\0';
	buf[1] = '\0';
	while ((rc = safe_read(&buf[0], &command, info)) >= 0 && buf[0] != '\n')
	{
		if (write(0, "\033[0K", 4) < 0)
		{
			ptr_free((void **)&command);
			all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
		}
		if (check_quotation(&command, buf) == true)
			continue ;
		check_return_value(rc, &command, buf[0], info);
	}
	if (buf[1] == '\'' || buf[1] == '\"')
		return (waiting_for_quotation(buf[1], &command, info));
	if (command[0] == '\0')
		return (newline_only(&(command)));
	return (command);
}
