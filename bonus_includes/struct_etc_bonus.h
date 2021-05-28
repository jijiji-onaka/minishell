/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_etc_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 23:44:40 by tjinichi          #+#    #+#             */
/*   Updated: 2021/05/26 13:42:11 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_ETC_BONUS_H
# define STRUCT_ETC_BONUS_H

# include <unistd.h>
# include <stdbool.h>
# include "standard_lib_bonus.h"

typedef struct s_string
{
	char				*str;
	size_t				len;
}						t_string;

typedef struct s_env
{
	struct s_string		key;
	struct s_string		value;
}						t_env;

typedef struct s_envlst
{
	struct s_env		env;
	struct s_envlst		*next;
	struct s_envlst		*qnext;
}						t_envlst;

typedef struct s_wild_lst
{
	char				*value;
	struct s_wild_lst	*next;
	struct s_wild_lst	*qnext;
}						t_wild_lst;

typedef struct s_hist_list
{
	char				*command;
	struct s_hist_list	*new_hist;
	struct s_hist_list	*old_hist;
}						t_hist_list;

typedef struct s_history
{
	char				file_path[1024];
	struct s_hist_list	*list;
	struct s_hist_list	*begin;
}						t_history;

typedef struct s_key
{
	char				*up;
	char				*down;
	char				*left;
	char				*right;
	char				*clean_right;
	char				*clean;
	char				*cursor_save;
	char				*cursor_restore;
	char				*cursor_invisible;
	char				*cursor_visible;
	char				*color_change;
	char				*color_reset;
	char				*scroll_up;
	char				*scroll_down;
	char				*delete_line;
	size_t				target_start;
	size_t				target_end;
	char				*target;
	size_t				save_command_len;
	bool				multi_byte_flag;
	bool				multi_byte_flag_2;
}						t_key;

typedef struct s_cursor
{
	int					cur_pos[2];
	int					command_start_pos[2];
	int					command_end_pos[2];
	int					select_pos[2];
}						t_cursor;

typedef struct s_minishell_info
{
	char				*current_dir_path;
	char				*oldpwd_path;
	bool				unset_pwd_flag;
	bool				unset_oldpwd_flag;
	bool				minishell_op_c;
	bool				minishell_op_no_edit;
	struct s_envlst		*env;
	struct s_cmdlst		*cmd_lst;
	struct s_history	history;
	struct s_key		key;
	struct s_cursor		cursor;
	struct termios		terminal[2];
	char				multiple_line_char;
	char				chr;
	int					cmd_lst_num;
	bool				exit_too_arg;
	char				*ptr_for_free;
	char				*ptr_for_free_2;
	char				**ptr_2d_for_free;
}						t_minishell;

typedef struct s_cmdlst
{
	int					type;
	int					fd;
	char				**arg;
	int					checker_pipe;
	int					checker_redir;
	struct s_cmdlst		*next;
}						t_cmdlst;

typedef struct s_cmd_grp
{
	char		***cmd_grp;
	int			array_size;
}						t_cmd_grp;

typedef struct s_str
{
	char		*str;
	int			prev_len;
}						t_str;

typedef struct s_global
{
	pid_t		fork_pid;
	pid_t		fork_pid_for_pipe;
	int			exit_status;
	int			sig_sign;
	t_minishell	info;
	bool		reading;
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
/*
**
*/
# define NOT_FOUND -1
# define CMD_NOT_FOUND 127
# define NEXT_CMD 2
# define QUO 0
# define B_SLA 1
# define DOLLAR 2
# define END_OF_THE_WORLD -1
# define ORIGINAL 0
# define REPLICA 1
# define MATCH 0
# define OLDPWD 1
/*
** KEY
*/
# define READ_SIZE 3
# define KEY_UP 0
# define KEY_DOWN 1
# define KEY_LEFT 2
# define KEY_RIGHT 3
# define CTRL_D 4
# define CTRL_L 5
# define KEY_DELETE 6
# define NORMAL_CHAR 7
# define KEY_NEWLINE 8
# define KEY_HOME 9
# define KEY_END 10
# define KEY_TAB 11
# define NOTHING_KEY 11
# define KEY_CTRL_LEFT 12
# define KEY_CTRL_RIGHT 13
# define KEY_SHIFT_LEFT 14
# define KEY_SHIFT_RIGHT 15
# define KEY_SHIFT_UP 16
# define CTRL_B 17
# define KEY_SHIFT_DOWN 18
# define CTRL_P 19
# define CTRL_N 20
# define TO_BE_CONTINUE 21
# define HOME 0
# define END 1
/*
** CURSOR || WINDOW
*/
# define X 0
# define Y 1
# define LEFT_EDGE 1
# define UPPER_EDGE 1
/*
** FD
*/
# define STDIN STDIN_FILENO
# define STDOUT STDOUT_FILENO
# define STDERR STDERR_FILENO

#endif
