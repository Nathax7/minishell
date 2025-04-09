NAME = pipex
NAME_BONUS = pipex_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
OBJ_DIR = obj
OBJ_DIR_BONUS = obj_bonus
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))
OBJ_BONUS = $(addprefix $(OBJ_DIR_BONUS)/, $(SRC_BONUS:%.c=%.o))
DEPS = $(OBJ:.o=.d)
DEPS_BONUS = $(OBJ_BONUS:.o=.d)
SRC = pipex.c utils.c
SRC_BONUS = pipex_bonus.c utils_bonus.c here_doc.c exec_bonus.c child_process.c

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
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L$(LIBFT_DIR) -lft

$(OBJ_DIR):
	@echo "$(WHITE) mkdir -p $(OBJ_DIR) $(NC)"
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

libft:
	make -C $(LIBFT_DIR)

bonus: $(LIBFT) $(OBJ_DIR_BONUS) $(NAME_BONUS)

$(OBJ_DIR_BONUS)/%.o: %.c Makefile libft/Makefile
	@echo "$(WHITE) mkdir -p $(dir $@) $(NC)"
	@mkdir -p $(dir $@)
	@echo "$(GREEN) $(CC) $(CFLAGS) -MMD -MP -o $@ -c $< -I$(LIBFT_DIR) $(NC)"
	@$(CC) $(CFLAGS) -MMD -MP -o $@ -c $< -I$(LIBFT_DIR)

-include $(DEPS_BONUS)

$(NAME_BONUS): $(OBJ_BONUS) $(LIBFT)
	@echo "$(GREEN) $(CC) $(CFLAGS) -o $(NAME) $(OBJ_BONUS) -L$(LIBFT_DIR) -lft $(NC)"
	@$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJ_BONUS) -L$(LIBFT_DIR) -lft

$(OBJ_DIR_BONUS):
	@echo "$(WHITE) mkdir -p $(OBJ_DIR_BONUS) $(NC)"
	@mkdir -p $(OBJ_DIR_BONUS)


clean:
	@echo "$(RED) rm -rf $(OBJ_DIR) $(NC)"
	@echo "$(RED) rm -rf $(OBJ_DIR_BONUS) $(NC)"
	@echo "$(RED) make -C $(LIBFT_DIR) clean $(NC)"
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_DIR_BONUS)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@echo "$(RED) rm -f $(NAME) $(NC)"
	@echo "$(RED) rm -f $(NAME_BONUS) $(NC)"
	@echo "$(RED) make -C $(LIBFT_DIR) fclean $(NC)"
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

re_bonus: fclean bonus

.PHONY: all clean fclean re libft bonus re_bonus