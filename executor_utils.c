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
		if (cmd->fd_in == -1 || cmd->fd_out == -1)
		{
			perror("Redirection error");
			exit(EXIT_FAILURE);
		}
		redir = redir->next;
	}
}

void	is_and_or(t_mini *mini)
{
	t_cmd	*cmd;

	cmd = mini->cmd_list;
	if (!cmd)
		return ;
	if (cmd->cond_type == AND && mini->exit_code != 0)
	{
		while (cmd && cmd->cond_type == AND)
			cmd = cmd->next;
	}
	else if (cmd->cond_type == OR && mini->exit_code == 0)
	{
		while (cmd && cmd->cond_type == OR)
			cmd = cmd->next;
	}
	mini->cmd_list = cmd->next;
}

void	close_updt_pipe(t_cmd *cmd, t_pipex *pipex)
{
	if (pipex->prev_fd != -1)
		close(pipex->prev_fd);
	if (cmd->next && cmd->cond_type != AND && cmd->cond_type != OR)
	{
		close(pipex->pipe_fd[1]);
		pipex->prev_fd = pipex->pipe_fd[0];
	}
	else
		pipex->prev_fd = -1;
}

void	path_found(t_cmd *cmd, t_mini *mini)
{
	if (!cmd->cmd_path)
	{
		write(2, "minishell: command not found: ", 30);
		write(2, cmd->args[0], 
			ft_strlen(cmd->args[0]));
		write(2, "\n", 1);
		exit(127);
	}
	execve(cmd->cmd_path, cmd->args, mini->env_arr);
	perror(cmd->args[0]);
	exit(126);
}
