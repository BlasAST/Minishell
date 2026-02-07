#include "minishell.h"

char	*join_free(char *s1, char *s2, char *s3)
{
	char	*joined;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1;
	joined = malloc(len);
	if (!joined)
		return (NULL);
	ft_strcpy(joined, s1);
	ft_strcat(joined, s2);
	ft_strcat(joined, s3);
	return (joined);
}

void	mng_redirections(t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redir_list;
	while (redir)
	{
		if (redir->redir_type == REDIR_IN)
			cmd->fd_in = open(redir->target, O_RDONLY);
		else if (redir->redir_type == REDIR_OUT)
			cmd->fd_out = open(redir->target, O_WRONLY
					| O_CREAT | O_TRUNC, 0644);
		else if (redir->redir_type == REDIR_APPEND)
			cmd->fd_out = open(redir->target, O_WRONLY
					| O_CREAT | O_APPEND, 0644);
		else if (redir->redir_type == HEREDOC)
			cmd->fd_in = heredoc(cmd);
		if (cmd->fd_in == -1 || cmd->fd_out == -1)
		{
			perror("Redirection error");
			exit(EXIT_FAILURE);
		}
		redir = redir->next;
	}
}

int	heredoc(t_cmd *cmd)
{
	int		heredoc[2];
	char	*limiter;
	char	*line;

	if (pipe(heredoc) < 0)
		perror("pipe");
	limiter = cmd->redir_list->target;
	while (1)
	{
		line = readline("heredoc> ");
		if (!line || ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		write(heredoc[1], line, ft_strlen(line));
		write(heredoc[1], "\n", 1);
		free(line);
	}
	close(heredoc[1]);
	return (heredoc[0]);
}
