NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
AR = ar rcs
RM = rm -rf

OBJ_DIR = obj

GREEN=\033[0;32m
BLUE=\033[38;2;64;224;208m
RED=\033[0;91m
WHITE=\033[2;37m
NC=\033[0m

DARK_YELLOW=\033[2;33m
YELLOW=\033[38;5;178m
DARK_GREEN=\033[38;5;22m
DARK_RED=\033[38;5;124m
BLACK=\033[0;30m
INV=\033[7m
FLASH=\033[5m

LIBFT_FILES = ft_atoi.c ft_isalnum.c ft_isdigit.c ft_memcmp.c ft_memset.c ft_strlcat.c ft_strncmp.c \
 ft_tolower.c ft_bzero.c ft_isalpha.c ft_isprint.c ft_memcpy.c ft_strchr.c ft_strchr2.c ft_strlcpy.c \
 ft_strnstr.c ft_toupper.c ft_calloc.c ft_isascii.c ft_memchr.c ft_memmove.c ft_strdup.c \
 ft_strlen.c ft_strrchr.c ft_itoa.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_strmapi.c ft_striteri.c \
 ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_split.c ft_strjoin_free.c

PRINTF_FILES = ft_printf/ft_len_putaddress.c ft_printf/ft_len_putchar.c ft_printf/ft_len_putnbr_hex.c \
	ft_printf/ft_len_putnbr.c ft_printf/ft_len_putstr.c ft_printf/ft_len_uputnbr.c ft_printf/ft_printf.c ft_printf/ft_iterative_count.c \
	ft_printf/len_putaddress_error.c ft_printf/len_putchar_error.c ft_printf/len_putnbr_hex_error.c ft_printf/exit_error.c\
	ft_printf/len_putnbr_error.c ft_printf/len_putstr_error.c ft_printf/len_uputnbr_error.c ft_printf/ft_printf_error.c ft_printf/iterative_count_error.c \


GNL_FILES = get_next_line/get_next_line.c get_next_line/get_next_line_bonus.c

LIBFT_BONUS_FILES = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstiter_bonus.c \
 ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstadd_back_bonus.c ft_lstmap_bonus.c

SRC_FILES = $(LIBFT_FILES) $(PRINTF_FILES) $(GNL_FILES) $(LIBFT_BONUS_FILES)

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:%.c=%.o))
DEPS = $(OBJ:.o=.d)

all: $(OBJ_DIR) $(NAME)

	@echo "$(BLUE)	             xxxxx"
	@echo "                  xXXXXXXXXXx"
	@echo "                 XXXXXXXXXXXXX"
	@echo "                xXXXXXXXX  XXXx"
	@echo "                XXXXXXXXX $(YELLOW)$(FLASH)0$(NC)$(BLUE)XXXX$(YELLOW)___$(NC)$(BLUE)"
	@echo "               xXXXXXXXXXxxXXXX$(YELLOW)____\\   $(GREEN) LIBFT COMPILED!🎉$(NC)$(BLUE)	"
	@echo "               XXXXXXXXXXXXXXXX$(YELLOW)____/$(NC)$(BLUE)"
	@echo "               XXXXXXXXXXXXXXXXX"
	@echo "               XXXXX|\XXX/|XXXXX"
	@echo "               XXXXX| \-/ |XXXXX"
	@echo "              xXXXXX| $(RED)[ ]$(NC)$(BLUE) |XXXXXx"
	@echo "            xXXXX   | /-\ |   XXXXx"
	@echo "         xXXXXX     |/   \|     XXXXXx"
	@echo "       xXXXXXX                   XXXXXXx"
	@echo "      xXXXXXXX                   XXXXXXXx"
	@echo "     xXXXXXXXX                   XXXXXXXXx"
	@echo "    xXXXXXXXXX                   XXXXXXXXXx"
	@echo "   xXXXXXXXXXX                   XXXXXXXXXXx"
	@echo "  xXXXXXXXXXXX                   XXXXXXXXXXXx"
	@echo " xXXXXXXXX XXX                   XXX XXXXXXXXx"
	@echo " XXXXXXXX  XXX                   XXX  XXXXXXXX"
	@echo "xXXXXXXX   XXX   $(GREEN)✨MINISHELL✨$(BLUE)   XXX   XXXXXXXx"
	@echo "XXXXXX     XXX                   XXX     XXXXXX"
	@echo "XXXX       XXX                   XXX       XXXX"
	@echo " XX        XXX                   XXX        XX"
	@echo "           XXX                   XXX"
	@echo "           XXX                   XXX"
	@echo "           XXX                   XXX"
	@echo "           XXX                   XXX"
	@echo "           XXXx                 xXXX"
	@echo "           XXXXXXXXXXXXXXXXXXXXXXXXX"
	@echo "           XXXXXXX           XXXXXXX"
	@echo "       $(YELLOW)____$(BLUE)XXXXXX             XXXXXX$(YELLOW)____"
	@echo "      /________/               \________\\ $(NC)"



$(OBJ_DIR)/%.o: %.c Makefile
	@echo "$(WHITE) mkdir -p $(dir $@) $(NC)"
	@mkdir -p $(dir $@)
	@echo "$(DARK_GREEN) $(CC) $(CFLAGS) -MMD -MP -o $@ -c $<$(NC)"
	@$(CC) $(CFLAGS) -MMD -MP -o $@ -c $<


-include $(DEPS)

$(NAME): $(OBJ)
	@echo "$(DARK_YELLOW) library created... $(NC)"
	@$(AR) $(NAME) $(OBJ)

$(OBJ_DIR):
	@echo "$(WHITE) mkdir -p $(OBJ_DIR) $(NC)"
	@mkdir -p $(OBJ_DIR)

clean:
	@echo "$(DARK_RED) $(RM) $(OBJ_DIR) $(NC)"
	@$(RM) $(OBJ_DIR)

fclean: clean
	@echo "$(DARK_RED) rm -f $(NAME) $(NC)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
