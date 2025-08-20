NAME		= minishell

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

SRC_DIR		= ./src
SRC_UTILS	= $(SRC_DIR)/utils
OBJ_DIR		= ./obj
INC_DIR		= ./inc


SRCS		= $(SRC_UTILS)/garbage_collector/ft_garbage_collector_one.c \
			  $(SRC_UTILS)/garbage_collector/ft_garbage_collector_two.c \
			  $(SRC_UTILS)/prompt/prompt.c \
			  $(SRC_UTILS)/prompt/prompt_utils.c \
			  $(SRC_UTILS)/prompt/prompt_utils_two.c \
			  $(SRC_UTILS)/prompt/prompt_craft.c \
			  $(SRC_UTILS)/signals/signal_prompt.c \
			  $(SRC_UTILS)/env/env_init.c \
			  $(SRC_DIR)/errors/errors.c \
			  $(SRC_DIR)/lexer/tokens.c \
			  $(SRC_DIR)/lexer/tokenizer.c \
			  $(SRC_DIR)/lexer/tokenizer_utils.c \
			  $(SRC_DIR)/main/main.c


OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

LIBFT_DIR	= $(INC_DIR)/libft
LIBFT		= $(LIBFT_DIR)/libft.a

READLINE	= -lreadline

INCLUDES	= -I./inc -I$(LIBFT_DIR)

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) $(READLINE) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re