/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 02:55:26 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/13 14:03:38 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../bonus_includes/minishell_bonus.h"

void	*ft_perror(char *err_message)
{
	char	*errno_message;

	if (write(STDERR, "minishell: ", 11) < 0)
		exit(EXIT_FAILURE);
	if (write(STDERR, err_message, ft_strlen(err_message)) < 0)
		exit(EXIT_FAILURE);
	if (write(STDERR, ": ", 2) < 0)
		exit(EXIT_FAILURE);
	errno_message = strerror(errno);
	if (write(STDERR, errno_message, ft_strlen(errno_message)) < 0)
		exit(EXIT_FAILURE);
	if (write(STDERR, "\n", 1) < 0)
		exit(EXIT_FAILURE);
	g_global.exit_status = EXIT_FAILURE;
	return (NULL);
}
