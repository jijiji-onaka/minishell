/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 01:24:25 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 17:33:08 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void		write_to_file(int fd, int std, t_cmdlst *begin,
					t_minishell_info *info)
{
	int	backup;

	if ((backup = dup(std)) == -1)
		all_free_exit(info, ERR_DUP, __LINE__, __FILE__);
	if (dup2(fd, std) == -1)
		all_free_exit(info, ERR_DUP2, __LINE__, __FILE__);
	execute_each_command(info, begin);
	if (dup2(backup, std) == -1)
		all_free_exit(info, ERR_DUP2, __LINE__, __FILE__);
	if (close(fd) == -1) // これはいらないかもdup2で勝手にクローズされる？
		all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	if (close(backup) == -1)
		all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);

/*
** もう一つのやり方
*/
	// if ((backup_stdout = dup(STDOUT_FILENO)) == -1)
	// 	all_free_exit(info, ERR_DUP, __LINE__, __FILE__);
	// if (close(STDOUT_FILENO) == -1)
	// 	all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	// if ((fd = open(filename, O_CREAT | O_WRONLY | mode, 0666)) == -1)
	// 	all_free_exit(info, ERR_OPEN, __LINE__, __FILE__);
	// execute_each_command(info, begin);
	// if (close(fd) == -1)
	// 	all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	// if (dup(backup_stdout) == -1)
	// 	all_free_exit(info, ERR_DUP, __LINE__, __FILE__);
}
