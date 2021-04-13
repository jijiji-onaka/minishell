/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:39:55 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/13 13:19:47 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include "struct_etc.h"
# include "standard_lib.h"

void	display_welcome_message(void);
void	put_prompt(t_minishell *info);
void	display_what_is_waiting_for(char chr, char **ptr1, char **ptr2,
			t_minishell *info);
char	*reset_prompt(char **ptr1, char **ptr2);

#endif
