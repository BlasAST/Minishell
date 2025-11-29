#ifndef MINISHELL_H
# define MINISHELL_H

# define _XOPEN_SOURCE 700
# define _GNU_SOURCE
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include "libft/libft.h"

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,      // '<'
	REDIR_OUT,     // '>'
	REDIR_APPEND,  // '>>'
	HEREDOC,       // '<<'
	END_OF_INPUT
}	t_token_type;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_token//list
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_cmd
{
	char			**args;
	char			*cmd_path;
	char			*redir_target;
	int				fd_in;
	int				fd_out;
	pid_t			pid;
	t_token_type	redir_type;
	struct s_cmd	*next;
} t_cmd;

typedef struct s_mini
{
	t_env		*env_list;
	t_token		*token_list;
	t_cmd		*cmd_list;
	char		**env_arr;
	int			exit_code;
	int			stdin_backup;
	int			stdout_backup;
}	t_mini;

// global variable to intercept the signal
extern int	g_signal_status;

void			tokenize_input(char *input, t_env *env);

void			add_token(t_token **list, t_token *new);
t_token			*new_token(t_token_type type, char *value);
t_token_type	get_type(char *s);
int				ispecial(char *c);


// Funciones de inicialización
void	init_mini(t_mini *mini, char **envp);

// Funciones entorno
t_env	*new_env_node(char *str);


//Funciones de señal
void	handle_sigint(int sig);

// Funciones limpieza
void	free_env_list(t_env *env_list);
#endif
