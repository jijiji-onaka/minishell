# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/23 20:15:31 by tjinichi          #+#    #+#              #
#    Updated: 2021/01/24 23:55:33 by tjinichi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

# =========== compile option ===================================================
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm
# =========== path =============================================================
INCLUDES = $(wildcard ./includes/*.h)
SRCDIR = ./srcs
OBJDIR = $(SRCDIR)/objs
#========== algorithm function ======================================================
ALGORITHM_DIR = $(SRCDIR)/algorithm_func
ALGORITHM_SRCS = $(addprefix $(ALGORITHM_DIR)/, \
				ft_swap.c \
				marge_strsort.c \
				str_bsearch.c \
)
# ========= convert function ===================================================
CONVERT_DIR = $(SRCDIR)/convert_func
CONVERT_SRCS = $(addprefix $(CONVERT_DIR)/, \
				ft_atoi.c \
				ft_itoa.c \
				ft_tolower.c \
				ft_toupper.c \
				ft_stod.c \
				ft_stoi.c \
				ft_stov.c \
				skip_space.c \
				str_tolower.c \
				ft_split.c \
				split_by_chrs.c \
)
#========== count function =====================================================
COUNT_DIR = $(SRCDIR)/count_func
COUNT_SRCS = $(addprefix $(COUNT_DIR)/, \
				count_2d.c \
				ft_numlen.c \
				ft_strlen.c \
)
#========== file function ======================================================
FILE_DIR = $(SRCDIR)/file_func
FILE_SRCS = $(addprefix $(FILE_DIR)/, \
				create_filename.c \
				get_next_line.c \
				get_next_line_utils.c \
				ft_close.c \
)
#========== free function ======================================================
FREE_DIR = $(SRCDIR)/free_func
FREE_SRCS = $(addprefix $(FREE_DIR)/, \
				ptr_2d_free.c \
				ptr_free.c \
)
#========== is_what function ===================================================
ISWHAT_DIR = $(SRCDIR)/iswhat_func
ISWHAT_SRCS = $(addprefix $(ISWHAT_DIR)/, \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_isspace.c \
				is_float.c \
)
#========== lst function =======================================================
LST_DIR = $(SRCDIR)/lst_func
LST_SRCS = $(addprefix $(LST_DIR)/, \
				ft_lstadd_back.c \
				ft_lstadd_front.c \
				ft_lstclear.c \
				ft_lstdelone.c \
				ft_lstiter.c \
				ft_lstlast.c \
				ft_lstmap.c \
				ft_lstnew.c \
				ft_lstsize.c \
)
#========== memory function ====================================================
MEMORY_DIR = $(SRCDIR)/memory_func
MEMORY_SRCS = $(addprefix $(MEMORY_DIR)/, \
				ft_bzero.c \
				ft_calloc.c \
				ft_memccpy.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memset.c \
)
#========== string function ====================================================
STRING_DIR = $(SRCDIR)/string_func
STRING_SRCS = $(addprefix $(STRING_DIR)/, \
				check_strtail.c \
				ft_str3join.c \
				ft_strchr.c \
				ft_strcmp.c \
				ft_strdup.c \
				ft_strjoin.c \
				ft_strjoinch.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strmapi.c \
				ft_strncmp.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_strtrim.c \
				ft_substr.c \
				strjoin_num.c \
				strtail_number.c \
				re_strjoinch.c \
				re_strdup.c \
				re_strjoin.c \
				strcmp_regardless_of_case.c \
				numjoin_str.c \
)
#========== 3Dvecter function ==================================================
VEC3D_DIR = $(SRCDIR)/vec3d_func
VEC3D_SRCS = $(addprefix $(VEC3D_DIR)/, \
				add_vec.c \
				crossproduct.c \
				distance_vec.c \
				dotproduct.c \
				intersect_point.c \
				length_vec.c \
				new_vec.c \
				normalize_vec.c \
				scal_times_vec.c \
				substruct_vec.c \
				cos_vec.c \
				scal_sub_vec.c \
)
#========== write function ====================================================
WRITE_DIR = $(SRCDIR)/write_func
WRITE_SRCS = $(addprefix $(WRITE_DIR)/, \
				ft_putchar_fd.c \
				ft_putstr_fd.c \
				ft_putnbr_fd.c \
				ft_putendl_fd.c \
				red_error.c \
				yellow_warning.c \
)
#========== Srcs and Objs ======================================================
SRCS = \
	$(ALGORITHM_SRCS) \
	$(CONVERT_SRCS)	\
	$(COUNT_SRCS)	\
	$(FILE_SRCS)	\
	$(FREE_SRCS)	\
	$(ISWHAT_SRCS)	\
	$(LST_SRCS)		\
	$(MEMORY_SRCS)	\
	$(STRING_SRCS)	\
	$(VEC3D_SRCS)	\
	$(WRITE_SRCS)	\

OBJS = $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))

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
# ========== Increment % =======================================================

T		=	$(words ${OBJS})
N		=	0
# words = 文字列の個数を数えます
# eval = 文字列を評価します
C		=	$(words $N)${eval N += 1}
ECHO	=	"[`expr $C  '*' 100 / $T`%]"

# ========== Make objs =========================================================
$(OBJDIR)/%.o : $(ALGORITHM_DIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW)$(ECHO) Compiling $(RESET)$(UNDER_LINE)"$@"$(RESET)"
$(OBJDIR)/%.o : $(CONVERT_DIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW)$(ECHO) Compiling $(RESET)$(UNDER_LINE)"$@"$(RESET)"
$(OBJDIR)/%.o : $(COUNT_DIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW)$(ECHO) Compiling $(RESET)$(UNDER_LINE)"$@"$(RESET)"
$(OBJDIR)/%.o : $(FILE_DIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW)$(ECHO) Compiling $(RESET)$(UNDER_LINE)"$@"$(RESET)"
$(OBJDIR)/%.o : $(FREE_DIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW)$(ECHO) Compiling $(RESET)$(UNDER_LINE)"$@"$(RESET)"
$(OBJDIR)/%.o : $(ISWHAT_DIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW)$(ECHO) Compiling $(RESET)$(UNDER_LINE)"$@"$(RESET)"
$(OBJDIR)/%.o : $(LST_DIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW)$(ECHO) Compiling $(RESET)$(UNDER_LINE)"$@"$(RESET)"
$(OBJDIR)/%.o : $(MEMORY_DIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW)$(ECHO) Compiling $(RESET)$(UNDER_LINE)"$@"$(RESET)"
$(OBJDIR)/%.o : $(STRING_DIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW)$(ECHO) Compiling $(RESET)$(UNDER_LINE)"$@"$(RESET)"
$(OBJDIR)/%.o : $(VEC3D_DIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW)$(ECHO) Compiling $(RESET)$(UNDER_LINE)"$@"$(RESET)"
$(OBJDIR)/%.o : $(WRITE_DIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf " %-100b\r" "$(YELLOW)$(ECHO) Compiling $(RESET)$(UNDER_LINE)"$@"$(RESET)"


# ========== Main Make =========================================================
$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@printf "\r                                                             \r$(GREEN)$(BOLD)created libft.a$(RESET)\n"

all:	$(NAME)

clean:
	@make clean -C ./srcs/vec3d_func
	@$(RM) -rf $(OBJDIR)

fclean: clean
	@make fclean -C ./srcs/vec3d_func
	@$(RM) -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
