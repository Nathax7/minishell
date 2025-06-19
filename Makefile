NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_ALL:%.c=%.o))
DEPS = $(OBJ:.o=.d)

SRC_EXEC =	src/exec/child_process.c	\
			src/exec/exec_cmd.c			\
			src/exec/exec_one.c			\
			src/exec/here_doc.c			\
			src/exec/open_files.c		\
			src/exec/parsing_cmd.c		\
			src/exec/parsing_exec.c		\
			src/exec/pipex.c			\
			src/exec/utils_cmd.c		\

# SRC_PARSING =	src/parsing/convert_token_list.c	\
# 				src/parsing/error.c					\
# 				src/parsing/expand_variable.c		\
# 				src/parsing/expander_utils.c		\
# 				src/parsing/expander.c				\
# 				src/parsing/lexer_utils.c			\
# 				src/parsing/lexer.c					\
# 				src/parsing/string_builder.c		\

SRC_UTILS = src/utils/free_struct.c		\
			src/utils/find_last.c		\
			src/utils/find_size.c		\
			src/utils/find_first.c		\



SRC_ALL = $(SRC_EXEC) $(SRC_UTILS) test/mainath.c

GREEN=\033[0;32m
BLUE=\033[38;2;64;224;208m
RED=\033[0;91m
WHITE=\033[2;37m
NC=\033[0m

all: $(LIBFT) $(OBJ_DIR) $(NAME)

$(OBJ_DIR)/%.o: %.c Makefile libft/Makefile
	@echo "$(WHITE) mkdir -p $(dir $@) $(NC)"
	@mkdir -p $(dir $@)
	@echo "$(GREEN) $(CC) $(CFLAGS) -MMD -MP -o $@ -c $< -I$(LIBFT_DIR) $(NC)"
	@$(CC) $(CFLAGS) -MMD -MP -o $@ -c $< -I$(LIBFT_DIR)

-include $(DEPS)

$(NAME): $(OBJ) $(LIBFT)
	@echo "$(GREEN) $(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L$(LIBFT_DIR) -lft $(NC)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L$(LIBFT_DIR) -lft -lreadline

$(OBJ_DIR):
	@echo "$(WHITE) mkdir -p $(OBJ_DIR) $(NC)"
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

libft:
	make -C $(LIBFT_DIR)

clean:
	@echo "$(RED) rm -rf $(OBJ_DIR) $(NC)"
	@echo "$(RED) make -C $(LIBFT_DIR) clean $(NC)"
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@echo "$(RED) rm -f $(NAME) $(NC)"
	@echo "$(RED) make -C $(LIBFT_DIR) fclean $(NC)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

re_bonus: fclean

.PHONY: all clean fclean re libft