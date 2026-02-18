#include "minishell.h"

int	handle_heredoc(t_cmd **cmd_list)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = *cmd_list;
	while (cmd)
	{
		redir = cmd->redir_list;
		while (redir)
		{
			if (redir->redir_type == HEREDOC)
			{
				cmd->fd_in = heredoc(redir->target);
				if (cmd->fd_in == -1)
					return (0);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (1);
}

int	heredoc(char *limiter)
{
	int		heredoc[2];
	char	*line;

	if (pipe(heredoc) < 0)
		return (perror("pipe"), -1);
	while (1)
	{
		line = readline("heredoc> ");
		add_history(line);
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
