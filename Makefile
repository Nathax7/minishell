# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/10 12:31:08 by almeekel          #+#    #+#              #
#    Updated: 2025/04/20 16:50:03 by almeekel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# # Makefile de test du tokenizer ;) #

# **************************************************************************** #
#                               Minishell – Makefile                            #
# **************************************************************************** #

# ———————————————————  CONFIG  ——————————————————— #
NAME        := minishell
TESTNAME    := parse_test

# compiler ------------------------------------------------------------------- #
CC      := cc
CFLAGS  := -Wall -Wextra -Werror

# directories ---------------------------------------------------------------- #
INC_DIR     := includes
SRC_DIR     := src
PAR_DIR     := $(SRC_DIR)/parsing
LIBFT_DIR   := libft

# library / includes --------------------------------------------------------- #
LIBFT_A     := $(LIBFT_DIR)/libft.a
INCLUDES    := -I$(INC_DIR) -I$(LIBFT_DIR)      # libft headers are usually here
READLINE    := -lreadline                       # add -ltermcap on some Linux

# parsing sources ------------------------------------------------------------ #
PAR_SRCS := \
	$(PAR_DIR)/tokenizer.c \
	$(PAR_DIR)/tokenizer_utils.c \
	$(PAR_DIR)/quote_handling.c \
	$(PAR_DIR)/expanser.c \
	$(PAR_DIR)/parser.c \
	$(PAR_DIR)/heredoc.c

MAIN_SRC    := $(SRC_DIR)/parsing_main.c
SRCS        := $(PAR_SRCS) $(MAIN_SRC)

OBJS        := $(SRCS:.c=.o)

# test ----------------------------------------------------------------------- #
TEST_SRC    := parse-test.c
TEST_OBJS   := $(TEST_SRC:.c=.o) $(PAR_SRCS:.c=.o)

# ———————————————————  RULES  ——————————————————— #
.PHONY: all clean fclean re test

all: $(NAME)

$(NAME): $(LIBFT_A) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $^ $(READLINE) -o $@

# automatic libft build
$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

# generic object rule
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# --------------------------------------------------------------------------- #
#                TEST:  make test   →  ./parse_test                           #
# --------------------------------------------------------------------------- #
test: $(LIBFT_A) $(TEST_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(TEST_OBJS) $(READLINE) -o $(TESTNAME)
	@echo "✔  Built $(TESTNAME). Run it with ./$(TESTNAME)"

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS) $(TEST_OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME) $(TESTNAME)

re: fclean all













# # Aliases #

# NAME		=	minishell
# CC			=	cc
# FLAGS		=	-Werror -Wall -Wextra -g3 $(IFLAGS)
# IFLAGS		=	-I $(INCS) -I $(LIBFT_DIR)includes/
# LFLAGS		=	-L libft -lft -lreadline

# INCS		=	inc/
# HEADER		=	$(addprefix $(INCS), minishell.h)
# LIBFT_H		=	$(addprefix $(LIBFT_DIR)includes/, libft.h)

# SRC_DIR		=	src/
# OBJ_DIR		=	obj/
# LIBFT_DIR	=	libft/


# # Sources & Objects #

# BUILTINS	=	cd				\
# 				echo			\
# 				env				\
# 				exit			\
# 				export_utils	\
# 				export			\
# 				pwd				\
# 				unset

# ENV			=	environment		\
# 				path			\
# 				init			\
# 				shlvl			\
# 				sort_env

# ERROR		=	builtin_err		\
# 				error_manager	\
# 				lexer_err		\
# 				parser_err

# EXEC		=	exec_utils		\
# 				executer

# LEXER		=	heredoc			\
# 				heredoc_utils	\
# 				lex_checks		\
# 				lex_quotes		\
# 				lex_utils		\
# 				lexer

# PARSING		=	expansions		\
# 				expand_utils	\
# 				parser_utils	\
# 				parser_check	\
# 				parser

# UTILS		=	clean_exit		\
# 				fd				\
# 				signal

# MAIN		=	minishell

# SRCS		=	$(addprefix $(SRC_DIR)builtins/, $(addsuffix .c, $(BUILTINS)))	\
# 				$(addprefix $(SRC_DIR)env/, $(addsuffix .c, $(ENV)))			\
# 				$(addprefix $(SRC_DIR)error/, $(addsuffix .c, $(ERROR)))		\
# 				$(addprefix $(SRC_DIR)exec/, $(addsuffix .c, $(EXEC)))			\
# 				$(addprefix $(SRC_DIR)lexer/, $(addsuffix .c, $(LEXER)))		\
# 				$(addprefix $(SRC_DIR)parser/, $(addsuffix .c, $(PARSING)))		\
# 				$(addprefix $(SRC_DIR)utils/, $(addsuffix .c, $(UTILS)))		\
# 				$(addprefix $(SRC_DIR), $(addsuffix .c, $(MAIN)))

# OBJS		=	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))

# # Rules #

# .DEFAULT_GOAL	:=	all

# all				:	force $(NAME)

# $(NAME)			:	$(OBJS)
# 				@echo "\nCompiling minishell"
# 				@$(CC) $(OBJ) $(FLAGS) -o $@ $(OBJS) $(LFLAGS)
# 				@echo "Done !"

# $(OBJ_DIR)%.o	:	$(SRC_DIR)%.c $(HEADER) $(LIBFT_H) Makefile | $(OBJ_DIR)
# 				@mkdir -p $(dir $@)
# 				@printf "Generating minishell objects... %-33.33s\r" $@
# 				@$(CC) $(FLAGS) -c $< -o $@

# $(OBJ_DIR)		:
# 				@mkdir -p $(OBJ_DIR)

# force			:
# 				@make -sC libft
# 				@if [ ! -f "libft/libft.a" ]; then	\
# 					echo "Making libft.a";			\
# 					make -sC libft;					\
# 				fi


# clean			:
# 				@if [ -d "$(OBJ_DIR)" ]; then					\
# 					echo "Cleaning minishell obj/ directory";	\
# 					rm -rf $(OBJ_DIR);							\
# 				fi
# 				@make -sC libft clean

# fclean			:	clean
# 				@if [ -f "minishell" ]; then			\
# 					echo "Cleaning program: minishell";	\
# 					rm -f $(NAME);						\
# 				fi
# 				@make -sC libft fclean


# re				:	fclean all

# .PHONY			:	all re clean fclean force