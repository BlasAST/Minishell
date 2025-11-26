NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -g
SRCS = main.c \
	token.c \
	inits.c \
	env.c \
	signal.c
DIR_LIBFT = libft
LIBFT = $(DIR_LIBFT)libft.a
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
		$(CC) $(CFLAGS) $(OBJS) $(DIR_LIBFT) -o $(NAME)
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
