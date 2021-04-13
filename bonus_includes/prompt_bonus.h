/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:39:55 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/13 13:51:37 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_BONUS_H
# define PROMPT_BONUS_H

# include "struct_etc_bonus.h"
# include "standard_lib_bonus.h"

void	display_welcome_message(void);
void	put_prompt(t_minishell *info);
void	display_what_is_waiting_for(char chr, char **ptr1, char **ptr2,
			t_minishell *info);
char	*reset_prompt(char **ptr1, char **ptr2);

#endif
