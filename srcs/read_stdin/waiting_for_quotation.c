/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting_for_quotation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 00:23:07 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 17:45:09 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*press_eof_while_looking(char match, char **inputs, \
				t_minishell_info *info, char **command)
{
	ptr_free((void **)inputs);
	ptr_free((void **)command);
	if (write(1, "minishell: unexpected EOF while looking for matching `", 54)
				< 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (write(1, &match, 1) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (write(1, "`\nminishell: syntax error: unexpected end of file\n", 50)
				< 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	return (NULL);
}

static bool	do_when_input_char_equal_newline(int count[2], char **inputs, \
				char first_quo)
{
	if ((count[0] & 1) == 1)
	{
		if ((count[1] & 1) == 0)
		{
			count[0] = 0;
			count[1] = 0;
			return (true);
		}
	}
	else
	{
		rm_chr_in_str(inputs, first_quo);
		count[0] = 0;
		count[1] = 0;
	}
	write(1, "> ", 2);
	return (false);
}

static char	*prepare_in_advance(int *num1, int *num2, t_minishell_info *info)
{
	char	*res;

	if (write(1, "> ", 2) < 0)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	if (!(res = ft_strdup("\n")))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	*num1 = 0;
	*num2 = 0;
	return (res);
}

static bool	check_buf_and_return_value(ssize_t rc, char buf, int count[2], \
			char first_quo)
{
	char	other_quo;

	if (first_quo == '\'')
		other_quo = '\"';
	else if (first_quo == '\"')
		other_quo = '\'';
	if (rc == 0)
		return (true);
	else if (rc != 0 && buf == first_quo)
		count[0]++;
	else if (rc != 0 && buf == other_quo)
		count[1]++;
	return (false);
}

char		*waiting_for_quotation(char first_quo, char **command, \
						t_minishell_info *info)
{
	ssize_t		rc;
	char		buf;
	char		*inputs;
	int			count[2];

	inputs = prepare_in_advance(&count[0], &count[1], info);
	while ((rc = safe_read(&buf, &inputs, info)) >= 0)
	{
		if (write(0, "\033[0K", 4) < 0)
		{
			ptr_free((void **)&inputs);
			all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
		}
		if (check_buf_and_return_value(rc, buf, count, first_quo) == true)
			return (press_eof_while_looking(first_quo, &inputs, info, command));
		if (buf == '\n')
			if (do_when_input_char_equal_newline(count, &inputs, first_quo))
				break ;
		if (!(inputs = re_strjoinch(&inputs, buf)))
			all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	}
	*command = re_strjoin(command, *command, inputs);
	rm_chr_in_str(command, first_quo);
	ptr_free((void **)&inputs);
	return (*command);
}
