/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:39:55 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 17:41:23 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include "struct_etc.h"
# include "standard_lib.h"

void	display_welcome_message(void);
void	put_prompt(t_minishell_info *info);

#endif
