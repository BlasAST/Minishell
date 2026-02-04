
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
    parse_tokens.c \
    executor.c \
    executor_utils.c \
    expander_utils.c \
    expander.c 

SRCS_BUILDINS = builds_ins/ft_echo.c \
                builds_ins/ft_cd.c \
                builds_ins/ft_pwd.c \
                builds_ins/ft_export.c \
                builds_ins/ft_unset.c \
                builds_ins/ft_env.c \
                builds_ins/ft_exit.c

# Generamos los nombres de los objetos (.o) en sus respectivas rutas
OBJS = $(SRCS:.c=.o)
OBJS_BUILDINS = $(SRCS_BUILDINS:.c=.o)

DIR_LIBFT = libft
LIBFT = $(DIR_LIBFT)/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make bonus -C $(DIR_LIBFT)
	@echo "Libft compiled"

# Regla para compilar los .c de la raíz
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para compilar los .c dentro de build_ins/
build_ins/%.o: build_ins/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(OBJS_BUILDINS)
	$(CC) $(CFLAGS) $(OBJS) $(OBJS_BUILDINS) $(LIBFT) $(READLINE_FLAGS) -o $(NAME)
	@echo "Minishell compiled"

clean:
	rm -f $(OBJS)
	rm -f $(OBJS_BUILDINS)
	@make -C $(DIR_LIBFT) clean

fclean: clean
	rm -f $(NAME)
	@make -C $(DIR_LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re


# NAME = minishell
# CC = cc
# # CFLAGS = -Wall -Wextra -Werror -I. -g
# READLINE_FLAGS = -lreadline
# SRCS = main.c \
# 	token.c \
# 	token_utils.c \
# 	inits.c \
# 	env.c \
# 	signal.c \
# 	frees.c \
# 	parse_tokens.c \
# 	executor.c \
# 	executor_utils.c \
# 	expander_utils.c \
# 	expander.c 

# SRCS_BUILDINS = build_ins/ft_echo.c \
#                 build_ins/ft_cd.c \
#                 build_ins/ft_pwd.c \
#                 build_ins/ft_export.c \
#                 build_ins/ft_unset.c \
#                 build_ins/ft_env.c \
#                 build_ins/ft_exit.c

# DIR_LIBFT = libft
# LIBFT = $(DIR_LIBFT)/libft.a
# DIR_OBJS = objs
# OBJS = $(addprefix $(DIR_OBJS)/, $(SRCS:.c=.o))
# DIR_BUILDS = $(SRCS_BUILDINS:.c=.o)
# all: $(LIBFT) $(NAME)

# $(LIBFT):
# 		make bonus -C $(DIR_LIBFT)
# 		@echo "Libft compiled"

# $(DIR_OBJS)/%.o: %.c
# 	@mkdir -p objs
# 	$(CC) $(CFLAGS) -c $< -o $@

# $(DIR_BUILDS)/%.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@


# $(NAME): $(OBJS) 
# 	$(CC) $(CFLAGS) $(OBJS) $(DIR_BUILDS) $(LIBFT) $(READLINE_FLAGS) -o $(NAME)
# 		@echo "Minishell compiled"

# clean:
# 		rm -rf $(DIR_OBJS)
# 		rm -f $(OBJS)
# 		make -C $(DIR_LIBFT) clean
# fclean:		clean
# 		rm -f $(NAME)
# 		make -C $(DIR_LIBFT) fclean
# re: fclean all
# .PHONY: all clean fclean re
