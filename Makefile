NAME = minishell
CC = cc
# CFLAGS = -Wall -Wextra -Werror -I. -g
READLINE_FLAGS = -lreadline
SRCS = main.c \
	token.c \
	token_utils.c \
	inits.c \
	env.c \
	signal.c \
	frees.c \
	parse_tokens.c
DIR_LIBFT = libft
LIBFT = $(DIR_LIBFT)/libft.a
DIR_OBJS = objs
OBJS = $(addprefix $(DIR_OBJS)/, $(SRCS:.c=.o))

all: $(LIBFT) $(NAME)

$(LIBFT):
		make bonus -C $(DIR_LIBFT)
		@echo "Libft compiled"

$(DIR_OBJS)/%.o: %.c
	@mkdir -p objs
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINE_FLAGS) -o $(NAME)
		@echo "Minishell compiled"

clean:
		rm -rf $(DIR_OBJS)
		rm -f $(OBJS)
		make -C $(DIR_LIBFT) clean
fclean:		clean
		rm -f $(NAME)
		make -C $(DIR_LIBFT) fclean
re: fclean all
.PHONY: all clean fclean re
