/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_from_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 01:22:34 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 17:33:08 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void		read_from_file(int fd, t_cmdlst *begin, t_minishell_info *info)
{
	int	backup;

	if ((backup = dup(STDIN_FILENO)) == -1)
		all_free_exit(info, ERR_DUP, __LINE__, __FILE__);
	if (dup2(fd, STDIN_FILENO) == -1)
		all_free_exit(info, ERR_DUP2, __LINE__, __FILE__);
	execute_each_command(info, begin);
	if (dup2(backup, STDIN_FILENO) == -1)
		all_free_exit(info, ERR_DUP2, __LINE__, __FILE__);
	if (close(fd) == -1) // これはいらないかもdup2で勝手にクローズされる？
		all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	if (close(backup) == -1)
		all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
/*
** もう一つのやり方
*/
	// if ((backup_stdin = dup(STDIN_FILENO)) == -1)
	// 	all_free_exit(info, ERR_DUP, __LINE__, __FILE__);
	// if (close(STDIN_FILENO) == -1)
	// 	all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	// if ((fd = open(filename, O_RDONLY)) == -1)
	// {
	// 	if (dup(backup_stdin) == -1)
	// 		all_free_exit(info, ERR_DUP, __LINE__, __FILE__);
	// 	if (errno == ENOENT)
	// 		return (err_no_such_file_or_directory(filename, info));
	// 	all_free_exit(info, ERR_OPEN, __LINE__, __FILE__);
	// }
	// execute_each_command(info, begin);
	// if (close(fd) == -1)
	// 	all_free_exit(info, ERR_CLOSE, __LINE__, __FILE__);
	// if (dup(backup_stdin) == -1)
	// 	all_free_exit(info, ERR_DUP, __LINE__, __FILE__);
}
