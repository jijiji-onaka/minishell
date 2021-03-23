/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_more_pipe_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 22:58:37 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/21 20:58:05 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell_bonus.h"

static char	**insert_2d_array(char **dst, char **src1, char **src2)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (src1[i])
	{
		dst[i] = src1[i];
		i++;
	}
	j = 0;
	while (src2[j])
	{
		dst[i + j] = src2[j];
		j++;
	}
	dst[i + j] = NULL;
	return (dst);
}

static int	add_command_group(char **split, t_cmd_grp *cmd_grp_info,
							int split_size, t_minishell *info)
{
	char	**res;
	char	***cmd_grp;
	int		array_size;

	cmd_grp = cmd_grp_info->cmd_grp;
	array_size = cmd_grp_info->array_size;
	if (!(res = malloc(sizeof(char *) * (split_size + array_size + 1))))
	{
		ptr_2d_free((void ***)cmd_grp, array_size);
		ptr_2d_free((void ***)&split, split_size);
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	}
	res = insert_2d_array(res, *cmd_grp, split);
	cmd_grp_info->array_size += split_size;
	ptr_2d_free((void ***)cmd_grp, 0);
	ptr_2d_free((void ***)&split, 0);
	*cmd_grp = res;
	return (NEXT_CMD);
}

int			check_more_pipe(char **inputs, t_cmd_grp *cmd_grp_info,
								t_minishell *info)
{
	char	**split;
	int		i;

	if ((*inputs)[0] == '\0')
		return (NEWLINE);
	if (!(split = split_each_parts(*inputs)))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	ptr_free((void **)inputs);
	i = 0;
	while (split[i])
	{
		if (i != 0 && split[i][0] == '|' && split[i][1] != '|' && !split[i + 1])
			return (add_command_group(split, cmd_grp_info, i + 1, info));
		if (check_format_of_command(&split, info) == false)
			return (false);
		i++;
	}
	add_command_group(split, cmd_grp_info, i, info);
	return (true);
}
