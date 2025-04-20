# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/10 12:31:08 by almeekel          #+#    #+#              #
#    Updated: 2025/04/20 17:44:22 by almeekel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC      := cc
CFLAGS  := -Wall -Wextra -Werror

INC_DIR := includes
PAR_DIR := src/parsing
LIBFT   := libft        # path to your libft
LIBFT_A := $(LIBFT)/libft.a

INCS    := -I$(INC_DIR) -I$(LIBFT)
READLINE:= -lreadline           # add -ltermcap if needed on Linux

# -------- source files ----------------------------------------------------- #
PAR_SRCS := \
    $(PAR_DIR)/tokenizer.c \
    $(PAR_DIR)/tokenizer_utils.c \
    $(PAR_DIR)/quote_handling.c \
    $(PAR_DIR)/expanser.c \
    $(PAR_DIR)/parser.c \
    $(PAR_DIR)/heredoc.c \
    $(PAR_DIR)/parsing.c

# Add utils sources (note the path seems unusual - check if "utils.c" is a directory)
UTILS_DIR := src/utils.c
UTILS_SRCS := \
    $(UTILS_DIR)/free_struct.c

TEST_SRC   := parse-test.c
TEST_OBJS  := $(TEST_SRC:.c=.o) $(PAR_SRCS:.c=.o) $(UTILS_SRCS:.c=.o)
TEST_BIN   := parse_test

# -------- rules ------------------------------------------------------------ #
.PHONY: all clean fclean re

all: $(TEST_BIN)

$(TEST_BIN): $(LIBFT_A) $(TEST_OBJS)
	$(CC) $(CFLAGS) $(INCS) $(TEST_OBJS) -o $@ -L$(LIBFT) -lft $(READLINE)

$(LIBFT_A):
	$(MAKE) -C $(LIBFT)

%.o: %.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	rm -f $(TEST_OBJS)
	$(MAKE) -C $(LIBFT) clean

fclean: clean
	rm -f $(TEST_BIN)
	$(MAKE) -C $(LIBFT) fclean

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