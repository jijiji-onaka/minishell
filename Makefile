# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/23 01:57:04 by tjinichi          #+#    #+#              #
#    Updated: 2021/04/10 16:21:47 by tjinichi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
# CFLAGS = -g -Wall -Werror -Wextra #            -fsanitize=address
CFLAGS = -g          -fsanitize=address

SRCFILE =	 \

SRCDIR = ./srcs
B_SRCDIR = ./bonus
OBJDIR = ./objs

#========== builtin function ===================================================
BUILTIN_DIR = $(SRCDIR)/builtin
BUILTIN_SRCS = $(addprefix $(BUILTIN_DIR)/, \
				bin/bin.c \
				bin/err_not_builtin.c \
				bin/get_environ.c \
				bin/search_binfile.c \
				cd/cd_utils.c \
				cd/cd_utils_2.c \
				cd/cd.c \
				cd/go_cwd.c \
				cd/go_oldpwd.c \
				cd/go_path.c \
				cd/is_cdpath.c \
				echo/echo.c \
				env/env.c \
				exit/exit.c \
				exit/set_numeric_flag.c \
				export/env_display.c \
				export/env_free.c \
				export/env_joint.c \
				export/env_is_valid.c \
				export/env_sort_2.c \
				export/env_sort.c \
				export/env_update.c \
				export/export.c \
				pwd/pwd.c \
				unset/unset.c \
				unset/env_remove.c \
)
$(OBJDIR)/%.o : $(BUILTIN_DIR)/bin/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
$(OBJDIR)/%.o : $(BUILTIN_DIR)/cd/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
$(OBJDIR)/%.o : $(BUILTIN_DIR)/echo/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
$(OBJDIR)/%.o : $(BUILTIN_DIR)/pwd/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
$(OBJDIR)/%.o : $(BUILTIN_DIR)/export/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
$(OBJDIR)/%.o : $(BUILTIN_DIR)/env/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
$(OBJDIR)/%.o : $(BUILTIN_DIR)/unset/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
$(OBJDIR)/%.o : $(BUILTIN_DIR)/exit/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
$(OBJDIR)/%.o : $(BUILTIN_DIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
#===============================================================================
#========== read stdin function ================================================
READ_DIR = $(SRCDIR)/read_stdin
READ_SRCS = $(addprefix $(READ_DIR)/, \
				format/check_format.c \
				key/ctrl_b.c  \
				key/ctrl_l.c \
				key/ctrl_d.c \
				key/ctrl_left_right.c \
				key/ctrl_p_n.c \
				key/delete.c \
				key/get_key_id.c \
				key/home_end.c \
				key/key_check.c \
				key/left_right.c \
				key/normal.c \
				key/shift_left_right.c \
				key/shift_up_down.c \
				key/up_down.c \
				window/display.c \
				window/get.c \
				window/move_cursor.c \
				window/win_utils_2.c \
				window/win_utils.c \
				read_command.c \
				read_quotation.c \
				read_add_command.c \
)
$(OBJDIR)/%.o : $(READ_DIR)/window/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
$(OBJDIR)/%.o : $(READ_DIR)/format/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
$(OBJDIR)/%.o : $(READ_DIR)/key/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
$(OBJDIR)/%.o : $(READ_DIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
#===============================================================================
#========== parse function ================================================
PARSE_DIR = $(SRCDIR)/parse
PARSE_SRCS = $(addprefix $(PARSE_DIR)/, \
				utils/binary_search.c \
				utils/cmdlst_add_back.c \
				utils/is_valid_quotation.c \
				utils/is_what.c \
				utils/is_what_2.c \
				utils/rm_spaces_in_2d_array.c \
				utils/split_each_arg.c \
				utils/split_each_parts.c \
				syntax/free_syntax_error.c \
				syntax/check_syntax.c \
				parse_command.c \
)
$(OBJDIR)/%.o : $(PARSE_DIR)/syntax/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
$(OBJDIR)/%.o : $(PARSE_DIR)/utils/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
$(OBJDIR)/%.o : $(PARSE_DIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
#===============================================================================
#========== prompt function ====================================================
PROMPT_DIR = $(SRCDIR)/prompt
PROMPT_SRCS = $(addprefix $(PROMPT_DIR)/, \
				display_welcome_message.c \
				put_prompt.c \
)
$(OBJDIR)/%.o : $(PROMPT_DIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
#===============================================================================
#========== execute function ===================================================
EXECUTE_DIR = $(SRCDIR)/execute
EXECUTE_SRCS = $(addprefix $(EXECUTE_DIR)/, \
				utils/at_first_change_only_env.c \
				utils/change_env_and_quo_and_slash.c \
				utils/change_env_and_quo_and_slash_2.c \
				utils/change_only_env.c \
				utils/change_only_env_2.c \
				utils/change_only_env_3.c \
				execute.c \
)
$(OBJDIR)/%.o : $(EXECUTE_DIR)/utils/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
$(OBJDIR)/%.o : $(EXECUTE_DIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
#===============================================================================
#========== separator function =================================================
SEPARATOR_DIR = $(SRCDIR)/pipe_redirect
SEPARATOR_SRCS = $(addprefix $(SEPARATOR_DIR)/, \
				utils/cleanup_redir.c \
				utils/close_pipe_fd.c \
				utils/connect_std_in_out_and_pipe.c \
				utils/err_message.c \
				utils/free_alloc_ptr_in_cmd_lst.c \
				utils/get_arg_behind_redir_for_redir_first.c \
				utils/get_arg_behind_redir.c \
				utils/pipe_utils.c \
				utils/prepare_redir.c \
				utils/redir_open_files_and_stock_fd.c \
				utils/skip_cmdlst.c \
				pipe.c \
				redir_first.c \
				redirect.c \
)
$(OBJDIR)/%.o : $(SEPARATOR_DIR)/utils/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
$(OBJDIR)/%.o : $(SEPARATOR_DIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
#===============================================================================
#========== minishell function =================================================
MINISHELL_DIR = $(SRCDIR)/minishell
MINISHELL_SRCS = $(addprefix $(MINISHELL_DIR)/, \
				setting/environ.c \
				setting/struct_all.c \
				setting/set_shell_level.c \
				setting/command_history.c \
				setting/command_history_2.c \
				setting/tgetent.c \
				ft_getenv.c \
				main.c \
				signal.c \
)
$(OBJDIR)/%.o : $(MINISHELL_DIR)/setting/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
$(OBJDIR)/%.o : $(MINISHELL_DIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
#===============================================================================
#========== error function =================================================
ERROR_DIR = $(SRCDIR)/error
ERROR_SRCS = $(addprefix $(ERROR_DIR)/, \
				all_free.c \
				error_exit.c \
				ft_perror.c \
				syntax_error.c \
				error_mandatory.c \
)
$(OBJDIR)/%.o : $(ERROR_DIR)/setting/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
$(OBJDIR)/%.o : $(ERROR_DIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
#===============================================================================
#========== safe_function function =================================================
SAFE_DIR = $(SRCDIR)/safe_function
SAFE_SRCS = $(addprefix $(SAFE_DIR)/, \
				dir.c \
				put_fd.c \
				safe_malloc.c \
				safe_read.c \
				safe_chdir.c \
)
$(OBJDIR)/%.o : $(SAFE_DIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
#===============================================================================

SRCS = \
	$(BUILTIN_SRCS) \
	$(READ_SRCS) \
	$(PARSE_SRCS) \
	$(PROMPT_SRCS) \
	$(EXECUTE_SRCS) \
	$(SEPARATOR_SRCS) \
	$(MINISHELL_SRCS) \
	$(ERROR_SRCS) \
	$(SAFE_SRCS) \

OBJS = $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))

LIBS = ./utils/Libft/
LIBFT = ./utils/Libft/libft.a

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS)  -o $(NAME) $(OBJS) $(LIBFT) -ltermcap
	@printf "\r                                                             \r$(GREEN)$(BOLD)created exe file [minishell]$(RESET)\n"

$(LIBFT): FORCE
	@make -C $(LIBS)

all: $(NAME)

clean:
	# @make clean -C $(LIBS)
	@rm -f $(OBJS)
	@rm -rf $(OBJDIR)
	@printf "$(RED)$(BOLD)[minishell] \nremoved object file and objs directory$(RESET)\n"

fclean:
	# @make fclean -C $(LIBS)
	@rm -rf $(OBJDIR)
	@printf "$(RED)$(BOLD)[minishell] \nremoved object file and objs directory\n"
	@rm -f $(NAME)
	@printf "removed minishell$(RESET)\n\n"

re: fclean all

leak: $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -g -o $(NAME) $(OBJS) $(LIBFT)
	./minishell

valgrind: $(LIBFT) $(OBJS)
	gcc -g -o $(NAME) $(OBJS) $(LIBFT)
	valgrind ./minishell


check:
	@cd minishell-helper && bash check.sh
check2:
	@cd minishell-helper && bash check1.sh
check1:
	@cd minishell-helper && bash test.sh

#========== builtin function ===================================================
BUILTIN_DIR = $(B_SRCDIR)/builtin
BUILTIN_B_SRCS = $(addprefix $(BUILTIN_DIR)/, \
				utils/cd_go_to_home_bonus.c \
				utils/cd_go_cwd_bonus.c \
				utils/cd_go_oldpwd_bonus.c \
				utils/cd_go_path_bonus.c \
				utils/cd_utils_bonus.c \
				utils/display_sorted_env_bonus.c \
				utils/envlst_sort_2_bonus.c \
				utils/envlst_sort_bonus.c \
				utils/error_mandatory_bonus.c \
				utils/exit_set_numeric_flag_bonus.c \
				utils/export_make_env_name_bonus.c \
				utils/export_make_env_value_bonus.c \
				utils/export_unset_is_parameter_bonus.c \
				utils/export_when_only_env_name_bonus.c \
				utils/safe_chdir_bonus.c \
				utils/ft_getenv_bonus.c \
				utils/search_exefile_bin_dir_bonus.c \
				utils/skip_for_exit_bonus.c \
				utils/two_ptr_free_bonus.c \
				utils/unset_remove_env_lst_if_bonus.c \
				utils/get_environ_bonus.c \
				utils/not_builtin_command_bonus.c \
				utils/update_env_lst_bonus.c \
				bin_bonus.c \
				cd_bonus.c \
				echo_bonus.c \
				env_bonus.c \
				exit_bonus.c \
				export_bonus.c \
				pwd_bonus.c \
				unset_bonus.c \
)
$(OBJDIR)/%.o : $(BUILTIN_DIR)/utils/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
$(OBJDIR)/%.o : $(BUILTIN_DIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
#===============================================================================
#========== read stdin function ================================================
READ_DIR = $(B_SRCDIR)/read_stdin
READ_B_SRCS = $(addprefix $(READ_DIR)/, \
				utils/ctrl_d_exit_bonus.c \
				utils/rm_chr_in_str_bonus.c \
				utils/safe_read_bonus.c \
				utils/reset_prompt_bonus.c \
				utils/check_more_pipe_bonus.c \
				utils/ctrl_d_rm_bonus.c \
				utils/what_is_waiting_for_bonus.c \
				read_command_bonus.c \
				read_quotation_bonus.c \
				read_add_command_bonus.c \
)
$(OBJDIR)/%.o : $(READ_DIR)/utils/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
$(OBJDIR)/%.o : $(READ_DIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
#===============================================================================
#========== parse function ================================================
PARSE_DIR = $(B_SRCDIR)/parse
PARSE_B_SRCS = $(addprefix $(PARSE_DIR)/, \
				utils/binary_search_bonus.c \
				utils/cmdlst_add_back_bonus.c \
				utils/is_what_bonus.c \
				utils/is_what_2_bonus.c \
				utils/rm_spaces_in_2d_array_bonus.c \
				utils/split_each_arg_bonus.c \
				utils/split_each_parts_bonus.c \
				utils/is_valid_quotation_bonus.c  \
				check_format/free_syntax_error_bonus.c \
				check_format/check_syntax_bonus.c \
				parse_command_bonus.c \
)
$(OBJDIR)/%.o : $(PARSE_DIR)/check_format/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
$(OBJDIR)/%.o : $(PARSE_DIR)/utils/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
$(OBJDIR)/%.o : $(PARSE_DIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
#===============================================================================
#========== prompt function ====================================================
PROMPT_DIR = $(B_SRCDIR)/prompt
PROMPT_B_SRCS = $(addprefix $(PROMPT_DIR)/, \
				display_welcome_message_bonus.c \
				put_prompt_bonus.c \
)
$(OBJDIR)/%.o : $(PROMPT_DIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
#===============================================================================
#========== execute function ===================================================
EXECUTE_DIR = $(B_SRCDIR)/execute
EXECUTE_B_SRCS = $(addprefix $(EXECUTE_DIR)/, \
				utils/at_first_change_only_env_bonus.c \
				utils/change_env_and_quo_and_slash_bonus.c \
				utils/change_env_and_quo_and_slash_2_bonus.c \
				utils/change_only_env_bonus.c \
				utils/change_only_env_2_bonus.c \
				utils/merge_lst_sort_bonus.c \
				utils/wild_card_utils_bonus.c \
				utils/wild_card_get_matched_files_bonus.c \
				utils/change_astarisk_bonus.c \
				utils/stock_envval_bonus.c \
				utils/return_index_bonus.c \
				execute_bonus.c \
				and_or_bonus.c \
)
$(OBJDIR)/%.o : $(EXECUTE_DIR)/utils/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
$(OBJDIR)/%.o : $(EXECUTE_DIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
#===============================================================================
#========== separator function =================================================
SEPARATOR_DIR = $(B_SRCDIR)/pipe_redirect
SEPARATOR_B_SRCS = $(addprefix $(SEPARATOR_DIR)/, \
				utils/cleanup_redir_bonus.c \
				utils/close_pipe_fd_bonus.c \
				utils/connect_std_in_out_and_pipe_bonus.c \
				utils/err_message_bonus.c \
				utils/do_here_document_bonus.c \
				utils/free_alloc_ptr_in_cmd_lst_bonus.c \
				utils/get_arg_behind_redir_for_redir_first_bonus.c \
				utils/get_arg_behind_redir_bonus.c \
				utils/pipe_utils_bonus.c \
				utils/prepare_redir_bonus.c \
				utils/redir_open_files_and_stock_fd_bonus.c \
				utils/skip_cmdlst_bonus.c \
				utils/change_env_in_here_doc_2_bonus.c  \
				utils/change_env_in_here_doc_bonus.c  \
				pipe_bonus.c \
				redir_first_bonus.c \
				redirect_bonus.c \
)
$(OBJDIR)/%.o : $(SEPARATOR_DIR)/utils/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
$(OBJDIR)/%.o : $(SEPARATOR_DIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
#===============================================================================
#========== minishell function =================================================
MINISHELL_DIR = $(B_SRCDIR)/minishell
MINISHELL_B_SRCS = $(addprefix $(MINISHELL_DIR)/, \
				setting/set_env_bonus.c \
				setting/set_minishell_bonus.c \
				setting/set_shell_level_bonus.c \
				main_bonus.c \
				signal_bonus.c \
)
$(OBJDIR)/%.o : $(MINISHELL_DIR)/setting/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
$(OBJDIR)/%.o : $(MINISHELL_DIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
#===============================================================================
#========== error function =================================================
ERROR_DIR = $(B_SRCDIR)/error
ERROR_B_SRCS = $(addprefix $(ERROR_DIR)/, \
				all_free_exit_bonus.c \
				ft_perror_exit_bonus.c \
				signal_error_exit_bonus.c \
				syntax_error_bonus.c \
)
$(OBJDIR)/%.o : $(ERROR_DIR)/setting/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
$(OBJDIR)/%.o : $(ERROR_DIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
#===============================================================================

B_SRCS = \
	$(BUILTIN_B_SRCS) \
	$(READ_B_SRCS) \
	$(PARSE_B_SRCS) \
	$(PROMPT_B_SRCS) \
	$(EXECUTE_B_SRCS) \
	$(SEPARATOR_B_SRCS) \
	$(MINISHELL_B_SRCS) \
	$(ERROR_B_SRCS) \


B_OBJS = $(addprefix $(OBJDIR)/, $(notdir $(B_SRCS:.c=.o)))

bonus:$(LIBFT) $(B_OBJS)
	@$(CC) $(CFLAGS)  -o $(NAME) $(B_OBJS) $(LIBFT)
	@printf "\r                                                                                    \r$(GREEN)$(BOLD)created exe file [minishell]$(RESET)\n"

.PHONY: all clean fclean re FORCE leak bonus

# =========== COLOR ============================================================
RESET		= \033[0m
RED			= \033[0;31m
GREEN		= \033[0;32m
YELLOW		= \033[0;33m
BLUE		= \033[0;34m
MAGENT		= \033[0;35m
CYAAN		= \033[0;36m
WHITE		= \033[0;37m
B_RESET		= \033[0;49m
B_YELLOW	= \033[0;43m
B_CYAAN		= \033[0;46m
BOLD		= \033[1m
UNDER_LINE	= \033[0;4m
