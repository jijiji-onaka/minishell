/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_etc_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 23:44:40 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/24 00:41:42 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_ETC_BONUS_H
# define STRUCT_ETC_BONUS_H

# include <unistd.h>
# include <stdbool.h>

typedef struct stat		t_stat;

typedef struct			s_envlst
{
	char				*value;
	struct s_envlst		*next;
	struct s_envlst		*qnext;
}						t_envlst;

typedef t_envlst		t_wild_lst;

typedef struct			s_minishell_info
{
	char				*current_dir_path;
	char				*oldpwd_path;
	bool				cwd_err_f;
	bool				minishell_op_c;
	struct s_envlst		*env;
	struct s_cmdlst		*cmd_lst;
	int					cmd_lst_num;
	int					exit_too_arg;
	char				*ptr_for_free;
	char				*ptr_for_free_2;
	char				**ptr_2d_for_free;
}						t_minishell;

typedef struct			s_cmdlst
{
	int					type;
	int					fd;
	char				**arg;
	int					checker_pipe;
	int					checker_redir;
	struct s_cmdlst		*next;
}						t_cmdlst;

typedef struct			s_cmd_grp
{
	char				***cmd_grp;
	int					array_size;
}						t_cmd_grp;

typedef struct			s_str
{
	char				*str;
	int					prev_len;
}						t_str;

typedef struct			s_global
{
	pid_t				fork_pid;
	pid_t				fork_pid_for_pipe;
	int					exit_status;
	int					sig_sign;
	bool				reading;
	t_minishell			info;
}						t_global;
t_global				g_global;

enum	e_cmd
{
	BIN,
	DB_AND,
	SEMICOLON,
	INPUT,
	DB_INPUT_,
	OUTPUT,
	DB_OUTPUT,
	CD,
	CMD_ECHO,
	ENV,
	EXPORT,
	PWD,
	UNSET,
	PIPE,
	DB_PIPE_,
	CMD_NUM,
};

enum	e_format
{
	NOT_SEPARATOR,
	F_AND,
	F_DB_AND,
	F_SEMICOLON,
	F_DB_SEMICOLON,
	F_INPUT,
	F_DB_INPUT,
	F_TR_INPUT,
	F_OUTPUT,
	F_DB_OUTPUT,
	F_OUTPUT_PIPE,
	F_PIPE,
	F_DB_PIPE,
	F_CMD_NUM,
};

# define NOT_CMD CMD_NUM

/*
** CMD_NUM + (1 ~ 8)
*/
# define DB_SEMICOLON 13
# define DB_PIPE 14
# define OUTPUT_PIPE 15
# define DB_INPUT 16
# define TR_INPUT 17
# define EXIT 18
# define OUTPUT_INPUT 19
# define DB_OUTPUT_INPUT 20
# define NOT_FOUND -1
# define CMD_NOT_FOUND 127
# define NEXT_CMD 2
# define QUO 0
# define B_SLA 1
# define DOLLAR 2
# define END_OF_THE_WORLD -1

#endif
