/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_file_name.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 02:24:47 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/11 21:30:31 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/file_func.h"

char				*create_file_name(char *directory,
				char *file, char *extension)
{
	char	*tmp;
	char	*extension_file;

	if (!directory || !file || !extension)
		return (NULL);
	tmp = ft_substr(file, ft_strrchr(file, '/') - file, \
		ft_strrchr(file, '.') - ft_strrchr(file, '/'));
	if (!tmp)
		return (NULL);
	extension_file = ft_str3join(directory, tmp, extension);
	free(tmp);
	if (!extension_file)
		return (NULL);
	return (extension_file);
}
