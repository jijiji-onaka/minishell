/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 02:55:26 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 17:08:18 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_perror(char *err_message)
{
	char	*errno_message;

	if (write(2, err_message, ft_strlen(err_message)) < 0)
		exit(EXIT_FAILURE);
	if (write(2, ":", 1) < 0)
		exit(EXIT_FAILURE);
	errno_message = strerror(errno);
	if (write(2, errno_message, ft_strlen(errno_message)) < 0)
		exit(EXIT_FAILURE);
	if (write(2, "\n", 1) < 0)
		exit(EXIT_FAILURE);
}

void		ft_perror_exit(char *error_message)
{
	ft_perror(error_message);
	exit(EXIT_FAILURE);
}
