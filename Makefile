# NAME = parser_core_test
# CC = gcc
# # Add -g for debugging, -fsanitize=address for memory errors
# CFLAGS = -Wall -Wextra -Werror -Iincludes -Ilibft # -g -fsanitize=address
# LDFLAGS = -Llibft -lft -lreadline
# RM = rm -f

# # Source directories
# PARSING_DIR = src/parsing
# TESTS_DIR = test

# # Core parsing source files to be tested
# PARSING_CORE_FILES = \
#     string_builder.c \
#     lexer.c \
#     lexer_utils.c \
#     convert_token_list.c \
#     error.c \
#     expand_variable.c \
#     expander_utils.c \
#     expander.c

# # Test main source file
# TEST_MAIN_FILE = main.c

# # Combine paths with filenames
# SRCS = $(addprefix $(PARSING_DIR)/, $(PARSING_CORE_FILES)) \
# 		$(addprefix $(TESTS_DIR)/, $(TEST_MAIN_FILE))

# OBJS = $(SRCS:.c=.o)

# # Libft
# LIBFT_DIR = libft
# LIBFT_A = $(LIBFT_DIR)/libft.a

# all: $(NAME)

# $(LIBFT_A):
# 	@$(MAKE) -C $(LIBFT_DIR) all

# $(NAME): $(LIBFT_A) $(OBJS)
# 	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)
# 	@echo "$(NAME) compiled!"

# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# clean:
# 	@$(MAKE) -C $(LIBFT_DIR) clean
# 	$(RM) $(OBJS)
# 	@echo "Core parser test object files cleaned."

# fclean: clean
# 	@$(MAKE) -C $(LIBFT_DIR) fclean
# 	$(RM) $(NAME)
# 	@echo "$(NAME) and libft cleaned."

# re: fclean all

# .PHONY: all clean fclean re





NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_ALL:%.c=%.o))
DEPS = $(OBJ:.o=.d)

SRC_EXEC =	src/exec/child_process.c			\
			src/exec/exec_bonus.c				\
			src/exec/here_doc.c					\
			src/exec/utils_bonus.c				\
			src/exec/pipex_bonus.c				\
			src/exec/exec_one.c					\
			src/exec/split_pipeline_group.c		\

SRC_PARSING =	src/parsing/convert_token_list.c	\
				src/parsing/error.c					\
				src/parsing/expand_variable.c		\
				src/parsing/expander_utils.c		\
				src/parsing/expander.c				\
				src/parsing/lexer_utils.c			\
				src/parsing/lexer.c					\
				src/parsing/string_builder.c		\

SRC_UTILS =	src/utils/ft_close.c		\
			src/utils/free_struct.c		\
			src/utils/utils.c			\
			src/utils/open.c			\
			src/utils/find_last.c		\
			src/utils/find_size.c		\



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