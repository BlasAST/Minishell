/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiguenc <bsiguenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 01:19:13 by blas              #+#    #+#             */
/*   Updated: 2026/02/27 14:07:00 by bsiguenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
	PIPE,
	AND,
	OR,
	END_OF_INPUT
}	t_token_type;

typedef struct s_token
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
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_parse_token
{
	t_cmd	*cmd_list;
	t_token	*tok;
	t_cmd	*cmd;
	t_cmd	*tmp;
	t_cmd	*prev;
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

typedef struct s_heredoc
{
	int		heredoc[2];
	char	*line;
	char	*clean_lim;
	char	*expanded;
	int		quote;
}	t_heredoc;

typedef struct s_executor
{
	t_pipex	pipex;
	int		status;
	t_cmd	*cmd;
	t_cmd	*prev;
	t_cmd	*runner;
	pid_t	wpid;
	pid_t	last_pid;
}	t_executor;


// global variable to intercept the signal
extern int		g_signal_status;

t_token			*tokenize_input(char *input);

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
void			free_token_list(t_token *token_list);
void			free_cmd_list(t_cmd *cmd_list);
void			free_all(t_mini *mini);

// Funciones expander
char			*remove_quotes(char *str);
void			expand_token(t_mini *mini, t_token *token);
void			expander(t_mini *mini);
char			*expand_heredoc(char *line, t_mini *mini);
char			*expand_variable(char *input, int *i, t_mini *mini);

t_cmd			*parser_tokens(t_token *tokens);

int				handle_heredoc(t_mini *mini);
int				heredoc(char *limiter, t_mini *mini);
// Funciones executor
void			executor(t_mini *mini);

char			*get_path(char *cmd, char **envp);
void			mng_redirections(t_cmd *cmd);
char			*join_path(char *s1, char *s2, char *s3);
void			is_and_or(t_cmd **cmd, t_mini *mini);
void			close_updt_pipe(t_cmd *cmd, t_pipex *pipex);
void			path_found(t_cmd *cmd, t_mini *mini);

int				is_env_builtin(char *cmd);
int				is_out_builtin(char *cmd);
int				run_builtin(t_cmd *cmd, t_mini *mini);

int				check_sintax(t_token *token_list);

// Manejo de errores
void			rerror(char *str, int error_status);
int				sintax_error(char *msg);
int				handle_sintax_error(t_mini *mini);
int				handle_heredoc_error(t_mini *mini, char *input);

int				update_env(t_mini *mini, char *key, char *value);
void			update_env_arr(t_mini *mini);
void			update_shlvl(t_mini *mini);

//builds-in
int				ft_cd(t_cmd *cmd, t_mini *mini);
int				ft_echo(t_cmd *cmd, t_mini *mini);
int				ft_env(t_cmd *cmd, t_mini *mini);
int				ft_exit(t_cmd *cmd, t_mini *mini);
int				ft_export(t_cmd *cmd, t_mini *mini);
int				ft_unset(t_cmd *cmd, t_mini *mini);
int				ft_pwd(t_cmd *cmd, t_mini *mini);

#endif
