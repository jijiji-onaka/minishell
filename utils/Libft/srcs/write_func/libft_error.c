/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 02:49:37 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/09 03:07:08 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/write_func.h"

void	*libft_error(t_err err, char *error_message)
{
	red_error();
	if (write(STDERR_FILENO, "Libft : ", 8) < 8)
		exit(EXIT_FAILURE);
	ft_putstr_fd(err.file, STDERR_FILENO);
	if (write(STDERR_FILENO, ":", 1) < 1)
		exit(EXIT_FAILURE);
	ft_putnbr_fd(err.line, STDERR_FILENO);
	if (write(STDERR_FILENO, " -> ", 4) < 4)
		exit(EXIT_FAILURE);
	ft_putendl_fd(error_message, STDERR_FILENO);
	return (NULL);
}
