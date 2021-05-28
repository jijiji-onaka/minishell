/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tgetent.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:16:39 by tjinichi          #+#    #+#             */
/*   Updated: 2021/05/24 23:56:57 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	set_key_2(t_minishell *info)
{
	info->key.cursor_invisible = tgetstr("vi", NULL);
	if (info->key.cursor_invisible == NULL)
		all_free_exit(info, ERR_TGETSTR, __LINE__, __FILE__);
	info->key.cursor_visible = tgetstr("ve", NULL);
	if (info->key.cursor_visible == NULL)
		all_free_exit(info, ERR_TGETSTR, __LINE__, __FILE__);
	info->key.scroll_up = tgetstr("sf", NULL);
	if (info->key.scroll_up == NULL || *(info->key.scroll_up) == '\0')
	{
		info->key.scroll_up = tgetstr("do", NULL);
		if (info->key.scroll_up == NULL || *(info->key.scroll_up) == '\0')
		{
			info->key.scroll_up = tgetstr("nl", NULL);
			if (info->key.scroll_up == NULL || *(info->key.scroll_up) == '\0')
				info->key.scroll_up = "\n";
		}
	}
	info->key.scroll_down = tgetstr("sr", NULL);
	info->key.delete_line = "\033[2K";
	info->key.color_change = "\x1b[38;5;106m\x1b[48;5;27m";
	info->key.color_reset = "\033[0m";
}

static void	set_key(t_minishell *info)
{
	info->key.up = "\033[A";
	info->key.down = "\033[B";
	info->key.left = tgetstr("le", NULL);
	if (info->key.left == NULL)
		all_free_exit(info, ERR_TGETSTR, __LINE__, __FILE__);
	info->key.right = tgetstr("nd", NULL);
	if (info->key.right == NULL)
		all_free_exit(info, ERR_TGETSTR, __LINE__, __FILE__);
	info->key.clean_right = tgetstr("ce", NULL);
	if (info->key.clean_right == NULL)
		all_free_exit(info, ERR_TGETSTR, __LINE__, __FILE__);
	info->key.clean = tgetstr("cl", NULL);
	if (info->key.clean == NULL)
		all_free_exit(info, ERR_TGETSTR, __LINE__, __FILE__);
	info->key.cursor_save = tgetstr("sc", NULL);
	if (info->key.cursor_save == NULL)
		all_free_exit(info, ERR_TGETSTR, __LINE__, __FILE__);
	info->key.cursor_restore = tgetstr("rc", NULL);
	if (info->key.cursor_restore == NULL)
		all_free_exit(info, ERR_TGETSTR, __LINE__, __FILE__);
	set_key_2(info);
}

static void	get_current_term_and_tgetent(t_minishell *info)
{
	char	*term;
	char	buf[1024];

	ft_bzero(buf, 1024);
	if (isatty(STDIN) == false)
		all_free_exit(info, ERR_ISATTY, __LINE__, __FILE__);
	term = ft_getenv("TERM", info->env, false);
	if (term == NULL)
		term = getenv("TERM");
	if (tgetent(buf, term) == false)
		all_free_exit(info, ERR_TGETENT, __LINE__, __FILE__);
}

void	set_term(t_minishell *info)
{
	tcgetattr(STDIN, &(info->terminal[ORIGINAL]));
	info->terminal[REPLICA] = info->terminal[ORIGINAL];
	info->terminal[REPLICA].c_lflag &= ~(ICANON | ECHO);
	info->terminal[REPLICA].c_cc[VMIN] = 1;
	info->terminal[REPLICA].c_cc[VTIME] = 0;
	tcsetattr(STDIN, TCSAFLUSH, &(info->terminal[REPLICA]));
	get_current_term_and_tgetent(info);
	set_key(info);
}

/*
** これにするとCtrl + Cをおそらくreadで読み込める
** info->terminal[REPLICA].c_lflag &= ~(ECHO | ICANON | ISIG);
*/
