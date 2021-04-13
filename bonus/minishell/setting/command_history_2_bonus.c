/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_history_2_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 07:33:47 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/13 14:03:24 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bonus_includes/minishell_bonus.h"

void	update_command_history_file(t_minishell *info, t_hist_list *history)
{
	int	fd;

	if (history == NULL)
		return ;
	fd = open(info->history.file_path, O_CREAT | O_RDWR, 0644);
	if (fd == -1)
		all_free_exit(info, ERR_OPEN, __LINE__, __FILE__);
	while (history->old_hist)
		history = history->old_hist;
	while (history)
	{
		if (history->command)
		{
			if (ft_putstr_fd(history->command, fd) == false)
				all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
			if (write(fd, "\n", 1) < 1)
				all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
		}
		history = history->new_hist;
	}
}
