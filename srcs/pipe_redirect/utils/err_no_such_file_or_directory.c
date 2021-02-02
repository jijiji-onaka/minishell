/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_no_such_file_or_directory.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 02:09:10 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 17:33:08 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool	err_no_such_file_or_directory(char *filename, t_minishell_info *info)
{
	if (write(STDERR_FILENO, "minishell: ", 11) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (ft_putstr_fd(filename, STDERR_FILENO) == false)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (write(STDERR_FILENO, ": No such file or directory\n", 28) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	return (false);
}
