NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -I includes
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_ALL:%.c=%.o))
DEPS = $(OBJ:.o=.d)

SRC_EXEC =	src/exec/child_process.c	\
			src/exec/exec_cmd.c			\
			src/exec/here_doc.c			\
			src/exec/parsing_cmd.c		\
			src/exec/parsing_exec.c		\
			src/exec/exec.c			\
			src/exec/utils_cmd.c		\
			src/exec/utils_cmd_struct.c	\
			src/exec/open_infiles.c		\
			src/exec/open_outfiles.c	\
			src/exec/find_path.c		\
			src/exec/redirections.c		\
			src/exec/exec_builtin.c		\

SRC_PARSING =	src/parsing/variable_expander.c			\
				src/parsing/token_expander.c			\
				src/parsing/field_splitter.c			\
				src/parsing/lexical_analyzer.c			\
				src/parsing/parser_main.c				\
				src/parsing/parser_core.c				\
				src/parsing/operator_processor.c		\
				src/parsing/quote_processor.c			\
				src/parsing/syntax_analyzer.c			\
				src/parsing/variable_processor.c 		\
				src/parsing/word_expander.c 			\
				src/parsing/word_tokenizer.c 			\
				src/parsing/token_expanding_processes.c \



SRC_UTILS = src/utils/search_last.c		\
			src/utils/size_calculator.c		\
			src/utils/search_first.c		\
			src/utils/expansion_helpers.c	\
			src/utils/string_constructor_ext.c\
			src/utils/string_constructor.c		\
			src/utils/builtin_helpers.c		\
			src/utils/structure_cleanup.c			\
			src/utils/structure_cleanup_ext.c	\
			src/utils/token_cleanup.c			\
			src/utils/error_handler.c	\
			src/utils/lexical_helpers.c			\
			src/utils/shell_environment.c 			\
			src/utils/environment_helpers.c 	\
			src/utils/variable_handler.c 		\
			src/utils/message_handler.c 	\
			src/utils/parent_cleanup.c 		\
			src/utils/child_cleanup.c 			\
			src/utils/safe_closer.c			\
			src/utils/quote_stripper.c		\
			src/utils/env_setting.c			\
			src/utils/spec_expansion_processing.c   \

SRC_BUILTINS =	src/builtins/builtin_export.c				\
				src/builtins/builtin_cd.c					\
				src/builtins/builtin_pwd.c					\
				src/builtins/builtin_echo.c					\
				src/builtins/builtin_env.c					\
				src/builtins/builtin_exit.c					\
				src/builtins/builtin_unset.c				\

SRC_SIGNALS = 	src/signal/signal_handlers.c		\
				src/signal/signal_setup.c		\

SRC_ALL = $(SRC_EXEC) $(SRC_UTILS) $(SRC_PARSING) $(SRC_SIGNALS) $(SRC_BUILTINS) main.c

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

$(LIBFT): FORCE
	make -C $(LIBFT_DIR)


FORCE:

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

.PHONY: all clean fclean re libft FORCE