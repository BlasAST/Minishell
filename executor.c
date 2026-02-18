#include "minishell.h"

char	*get_path(char *cmd, char **envp)
{
	t_get_path	gp;

	gp = (t_get_path){0};
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	while (envp && envp[gp.i])
	{
		if (ft_strncmp(envp[gp.i], "PATH=", 5) == 0)
		{
			gp.path = envp[gp.i] + 5;
			gp.paths = ft_split(gp.path, ':');
			gp.j = 0;
			while (gp.paths && gp.paths[gp.j])
			{
				gp.full = join_free(gp.paths[gp.j], "/", cmd);
				if (access(gp.full, X_OK) == 0)
					return (ft_free_split(gp.paths), gp.full);
				free(gp.full);
				gp.j++;
			}
			ft_free_split(gp.paths);
		}
		gp.i++;
	}
	return (NULL);
}

void	child_process(t_cmd *cmd, t_mini *mini, t_pipex *pipex)
{
	mng_redirections(cmd);
	if (cmd->fd_in != STDIN_FILENO)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	else if (pipex->prev_fd != -1)
	{
		dup2(pipex->prev_fd, STDIN_FILENO);
		close(pipex->prev_fd);
	}
	if (cmd->fd_out != STDOUT_FILENO)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
	else if (cmd->next)
	{
		close(pipex->pipe_fd[0]);
		dup2(pipex->pipe_fd[1], STDOUT_FILENO);
		close(pipex->pipe_fd[1]);
	}
	if (cmd->args && is_out_builtin(cmd->args[0]))
		exit(run_builtin(cmd, mini));
}

void	no_args(t_cmd *cmd, t_pipex *pipex)
{
	if (pipex->prev_fd != -1)
	{
		dup2(pipex->prev_fd, STDIN_FILENO);
		close(pipex->prev_fd);
	}
	if (cmd->next)
	{
		close(pipex->pipe_fd[0]);
		dup2(pipex->pipe_fd[1], STDOUT_FILENO);
		close(pipex->pipe_fd[1]);
	}
	mng_redirections(cmd);
	exit(0);
}

void	executor2(t_mini *mini, t_cmd *cmd, t_pipex *pipex)
{
	if (cmd->next)
		if (pipe(pipex->pipe_fd) == -1)
			perror("pipe");
	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		perror("fork");
		if (cmd->next)
		{
			close(pipex->pipe_fd[0]);
			close(pipex->pipe_fd[1]);
		}
		return ;
	}
	if (cmd->pid == 0)
	{
		if (!cmd->args || !cmd->args[0])
			no_args(cmd, pipex);
		child_process(cmd, mini, pipex);
		if (!cmd->cmd_path)
			cmd->cmd_path = get_path(cmd->args[0], mini->env_arr);
		path_found(cmd, mini);
	}
	else
		close_updt_pipe(cmd, pipex);
}

void	executor(t_mini *mini)
{
	t_pipex	pipex;
	int		status;

	pipex.prev_fd = -1;
	while (mini->cmd_list)
	{
		if (mini->cmd_list->args && mini->cmd_list->args[0]
			&& is_env_builtin(mini->cmd_list->args[0]) && !mini->cmd_list->next)
			mini->exit_code = run_builtin(mini->cmd_list, mini);
		else
		{
			executor2(mini, mini->cmd_list, &pipex);
			waitpid(mini->cmd_list->pid, &status, 0);
			if (WIFEXITED(status))
				mini->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				mini->exit_code = 128 + WTERMSIG(status);
		}
		is_and_or(mini);
	}
	while (wait(&status) > 0)
		;
}
