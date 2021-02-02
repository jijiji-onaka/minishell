# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/23 01:57:04 by tjinichi          #+#    #+#              #
#    Updated: 2021/02/02 17:50:19 by tjinichi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAGS = -g -Wall -Werror -Wextra                -fsanitize=address
# CFLAGS = -g     -fsanitize=address

SRCFILE =	 \

SRCDIR = ./srcs
OBJDIR = ./objs

#========== builtin function ===================================================
BUILTIN_DIR = $(SRCDIR)/builtin
BUILTIN_SRCS = $(addprefix $(BUILTIN_DIR)/, \
				utils/error_mandatory.c \
				utils/is_symbolic_link.c \
				utils/trace_symbolic_src.c \
				utils/search_env.c \
				utils/update_env_lst.c \
				bin.c \
				cd.c \
				echo.c \
				env.c \
				exit.c \
				export.c \
				pwd.c \
				unset.c \
)
$(OBJDIR)/%.o : $(BUILTIN_DIR)/utils/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
$(OBJDIR)/%.o : $(BUILTIN_DIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
#===============================================================================
#========== read stdin function ================================================
READ_DIR = $(SRCDIR)/read_stdin
READ_SRCS = $(addprefix $(READ_DIR)/, \
				utils/add_command_group.c \
				utils/ctrl_d_exit.c \
				utils/rm_chr_in_str.c \
				utils/safe_read.c \
				waiting_for_input.c \
				waiting_for_quotation.c \
				waiting_for_next_command.c \
)
$(OBJDIR)/%.o : $(READ_DIR)/utils/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
$(OBJDIR)/%.o : $(READ_DIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
#===============================================================================
#========== parse function ================================================
PARSE_DIR = $(SRCDIR)/parse
PARSE_SRCS = $(addprefix $(PARSE_DIR)/, \
				utils/add_back_command_lst.c \
				utils/dollar_switch_env_value.c \
				utils/is_command_exit.c \
				utils/isalnum_except_next_redir.c \
				utils/split_each_parts.c \
				utils/split_and_switch_env_value.c \
				utils/rm_spaces_in_2d_array.c \
				check_format/utils/ptr_2d_free_and_syntax_error.c \
				check_format/check_format_of_command.c \
				check_format/is_output_format_error.c \
				check_format/is_pipe_format_error.c \
				check_format/is_semicolon_format_error.c \
				parse_command.c \
)
$(OBJDIR)/%.o : $(PARSE_DIR)/utils/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
$(OBJDIR)/%.o : $(PARSE_DIR)/check_format/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
$(OBJDIR)/%.o : $(PARSE_DIR)/check_format/utils/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
$(OBJDIR)/%.o : $(PARSE_DIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
#===============================================================================
#========== prompt function ====================================================
PROMPT_DIR = $(SRCDIR)/prompt
PROMPT_SRCS = $(addprefix $(PROMPT_DIR)/, \
				display_welcome_message.c \
				put_prompt.c \
)
$(OBJDIR)/%.o : $(PROMPT_DIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
#===============================================================================
#========== execute function ===================================================
EXECUTE_DIR = $(SRCDIR)/execute
EXECUTE_SRCS = $(addprefix $(EXECUTE_DIR)/, \
				execute.c \
)
$(OBJDIR)/%.o : $(EXECUTE_DIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
#===============================================================================
#========== redirecet function =================================================
SEPARATOR_DIR = $(SRCDIR)/pipe_redirect
SEPARATOR_SRCS = $(addprefix $(SEPARATOR_DIR)/, \
				utils/close_pipe_fd.c \
				utils/connect_std_in_out_and_pipe.c \
				utils/err_no_such_file_or_directory.c \
				utils/free_alloc_ptr_in_cmd_lst.c \
				utils/mix_input_and_output.c \
				utils/mix_input_and_stderr_output.c \
				utils/open_files_and_stock_fd.c \
				utils/read_from_file.c \
				utils/skip_lst_and_free.c \
				utils/write_to_file.c \
				redirect.c \
				pipe.c \
)
$(OBJDIR)/%.o : $(SEPARATOR_DIR)/utils/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
$(OBJDIR)/%.o : $(SEPARATOR_DIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
#===============================================================================
#========== minishell function =================================================
MINISHELL_DIR = $(SRCDIR)/minishell
MINISHELL_SRCS = $(addprefix $(MINISHELL_DIR)/, \
				setting/set_env.c \
				setting/set_minishell_info.c \
				setting/set_prompt_message.c \
				setting/set_shell_level.c \
				main.c \
				signal.c \
)
$(OBJDIR)/%.o : $(MINISHELL_DIR)/setting/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
$(OBJDIR)/%.o : $(MINISHELL_DIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
#===============================================================================
#========== error function =================================================
ERROR_DIR = $(SRCDIR)/error
ERROR_SRCS = $(addprefix $(ERROR_DIR)/, \
				all_free_exit.c \
				ft_perror_exit.c \
				signal_error_exit.c \
				syntax_error.c \
)
$(OBJDIR)/%.o : $(ERROR_DIR)/setting/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
$(OBJDIR)/%.o : $(ERROR_DIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "$(YELLOW) Compiled $(RESET)$(UNDER_LINE)"$<"$(RESET)"
#===============================================================================

SRCS = \
	$(addprefix $(SRCDIR)/, $(SRCFILE)) \
	$(BUILTIN_SRCS) \
	$(READ_SRCS) \
	$(PARSE_SRCS) \
	$(PROMPT_SRCS) \
	$(EXECUTE_SRCS) \
	$(SEPARATOR_SRCS) \
	$(MINISHELL_SRCS) \
	$(ERROR_SRCS) \

OBJS = $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

LIBS = ./utils/Libft/
LIBFT = ./utils/Libft/libft.a

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS)  -o $(NAME) $(OBJS) $(LIBFT)

$(LIBFT): FORCE
	@make -C $(LIBS)

all: $(NAME)

clean:
	@make clean -C $(LIBS)
	rm -f $(OBJS)
	rm -rf $(OBJDIR)

fclean: clean
	@make fclean -C $(LIBS)
	rm -f $(NAME)

re: fclean all

leak: $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -g -o $(NAME) $(OBJS) $(LIBFT)
	./minishell

valgrind: $(LIBFT) $(OBJS)
	gcc -g -o $(NAME) $(OBJS) $(LIBFT)
	valgrind ./minishell

.PHONY: all clean fclean re FORCE leak

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
