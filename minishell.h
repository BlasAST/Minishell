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
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
	AND,
	OR,
	END_OF_INPUT
}	t_token_type;

typedef struct s_token//list
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_redir
{
	t_token_type	redir_type;
	char			*target;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**args;
	char			*cmd_path;
	t_redir			*redir_list;
	int				fd_in;
	int				fd_out;
	pid_t			pid;
	t_token_type	redir_type;
	t_token_type	cond_type;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_parse_token
{
	t_cmd	*cmd_list;
	t_token	*tok;
	t_cmd	*cmd;
	t_cmd	*tmp;
	int		arg_count;
	int		i;
}	t_parse_token;

typedef struct s_parse_word
{
	char	*buf;
	char	quote;
	int		start;
	char	*segment;
	char	*tmp;
	char	*exp;
}	t_parse_word;

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

typedef struct s_pipex
{
	int	pipe_fd[2];
	int	prev_fd;
	int	status;
}	t_pipex;

typedef struct s_get_path
{
	char	**paths;
	char	*full;
	char	*path;
	int		i;
	int		j;
}	t_get_path;

typedef int	(*t_builtin_func)(t_cmd *cmd, t_mini *mini);

typedef struct s_builtin
{
	char			*name;
	t_builtin_func	func;
}	t_builtin;

// global variable to intercept the signal
extern int		g_signal_status;

t_token			*tokenize_input(char *input, t_env *env);

void			add_token(t_token **list, t_token *new);
t_token			*new_token(t_token_type type, char *value);
t_token_type	get_type(char *s);
int				ispecial(char *c);

// Funciones de inicialización
void			init_mini(t_mini *mini, char **envp);

// Funciones entorno
t_env			*new_env_node(char *str);
int				*get_value_env(t_env *env, char *str, char **send);
int				*get_value_env(t_env *env, char *str, char **send);
int				find_path(t_env *env, char *str);

//Funciones de señal
void			handle_sigint(int sig);

// Funciones limpieza
void			free_env_list(t_env *env_list);

// Funciones expander
char			*remove_quotes(char *str);
void			expand_token(t_mini *mini, t_token *token);
void			expander(t_mini *mini);
void			run_herdoc(t_mini *mini, t_token *token);

t_cmd			*parser_tokens(t_token *tokens);

void			executor(t_cmd *cmd_list, t_mini *mini);

void			mng_redirections(t_cmd *cmd);
int				heredoc(t_cmd *cmd);
char			*join_free(char *s1, char *s2, char *s3);

int				is_env_builtin(char *cmd);
int				is_out_builtin(char *cmd);
int				run_builtin(t_cmd *cmd, t_mini *mini);

// Manejo de errores
void			rerror(char *str, int error_status);

//temp
void			free_cmd_list(t_cmd *cmd);
int	update_env(t_mini *mini, char *key, char *value);

//builds-in
int				ft_cd(t_cmd *cmd, t_mini *mini);
int				ft_echo(t_cmd *cmd);
int				ft_env(t_cmd *cmd, t_mini *mini);
int				ft_exit(t_cmd *cmd, t_mini *mini);
int				ft_export(t_cmd *cmd, t_mini *mini);
int				ft_unset(t_cmd *cmd, t_mini *mini);
int				ft_pwd(t_cmd *cmd);

// int	ft_cd(char **args, t_mini *mini);
// void	ft_echo(char *val);
// int	ft_env(t_mini *mini);
// int	ft_exit(char **args, t_mini *mini);
// int	ft_export(char **args, t_mini *mini);
// int	ft_unset(char **args, t_mini *mini);
// int	ft_pwd(void);
int	is_env_builtin(char *cmd);
int	is_out_builtin(char *cmd);
void	free_all(t_mini *mini);
#endif
