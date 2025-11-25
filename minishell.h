#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

typedef enum e_token_type
{
	WORD
	PIPE
	REDIR_IN      // '<'
	REDIR_OUT     // '>'
	REDIR_APPEND  // '>>'
	HEREDOC       // '<<'
	END_OF_INPUT
}	t_token_type;

typedef struct s_env//lista enlazada
{
	char			*key;
	char			*value;
	struct s_env	*next;
} t_env;

typedef struct s_token//
{
	t_token_type		type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
} t_token;

typedef struct s_cmd
{
	char			**args;
	char 			*cmd_path;
	char			*redir_target;
	int				fd_in;
	int				fd_out;
	pid_t			pid;
	t_token_type	redir_type;
	struct s_cmd	*next;
} t_cmd;

typedef struct s_mini
{
	t_env	*env_list;
	t_token	*token_list;
	t_cmd	*cmd_list;
	char 	**env_arr;
	int		exit_code;
	int		stdin_backup;
	int		stdout_backup;
} t_mini;
#endif
