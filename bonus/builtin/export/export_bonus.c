/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 17:56:17 by tjinichi          #+#    #+#             */
/*   Updated: 2021/05/22 14:03:19 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bonus_includes/minishell_bonus.h"

static void	two_free(void **one, void **two)
{
	ptr_free((void **)one);
	ptr_free((void **)two);
}

static bool	preparation(char *first_arg, t_minishell *info, int *i)
{
	if (first_arg == NULL)
	{
		display_sorted_env(info);
		return (false);
	}
	if (first_arg[0] == '-')
	{
		error_mandatory(ERR_EXPORT, 30, info);
		return (false);
	}
	*i = 0;
	return (true);
}

static t_string	make_key(char *src, t_minishell *info)
{
	t_string	res;

	if (src == NULL)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	res.str = src;
	res.len = ft_strlen(src);
	return (res);
}

static t_string	make_value(char *src, bool is_val, t_minishell *info)
{
	t_string	res;

	if (is_val)
	{
		res.str = NULL;
		res.len = 0;
		return (res);
	}
	res.str = ft_strdup(src);
	if (res.str == NULL)
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	res.len = ft_strlen(src);
	return (res);
}

void	exec_export(t_minishell *info, t_cmdlst *cmd)
{
	t_string	key;
	t_string	value;
	int			i;
	char		*equ_ptr;
	size_t		key_len;

	g_global.exit_status = 0;
	if (preparation(cmd->arg[1], info, &i) == false)
		return ;
	while (cmd->arg[++i])
	{
		equ_ptr = ft_strchr(cmd->arg[i] + 1, '=');
		if (equ_ptr == NULL)
			key_len = -1;
		else
			key_len = equ_ptr - cmd->arg[i];
		key = make_key(ft_substr(cmd->arg[i], 0, key_len), info);
		value = make_value(cmd->arg[i] + key_len + 1, equ_ptr == NULL, info);
		if (equ_ptr && key.str[key.len - 1] == '+')
			joint_env_value(&key, &value, info);
		if (is_valid_env_name(&(key.str), cmd->arg[i], 1, info))
			update_env_lst(&(info->env), key, value, info);
		else
			two_free((void **)&(key.str), (void **)&(value.str));
	}
}
