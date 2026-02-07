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

void	child_process(t_cmd *cmd, t_mini *mini)
{
	mng_redirections(cmd);
	if (cmd->fd_in != STDIN_FILENO)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	if (cmd->fd_out != STDOUT_FILENO)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
	if (!cmd->cmd_path)
		cmd->cmd_path = get_path(cmd->args[0], mini->env_arr);
	if (!cmd->cmd_path)
	{
		write(2, "minishell: command not found: ", 30);
		write(2, cmd->args[0], ft_strlen(cmd->args[0]));
		write(2, "\n", 1);
		exit(127);
	}
	execve(cmd->cmd_path, cmd->args, mini->env_arr);
	perror(cmd->args[0]);
	exit(126);
}

void	executor3(t_mini *mini, t_pipex pipex, int status)
{
	if (pipex.prev_fd != -1)
		close(pipex.prev_fd);
	if (mini->cmd_list->next)
	{
		close(pipex.pipe_fd[1]);
		pipex.prev_fd = pipex.pipe_fd[0];
	}
	else
		pipex.prev_fd = -1;
	waitpid(mini->cmd_list->pid, &status, 0);
	mini->exit_code = WEXITSTATUS(status);
}

void	executor2(t_mini *mini, t_pipex pipex, int status)
{
	if (mini->cmd_list->next)
		if (pipe(pipex.pipe_fd) == -1)
			perror("pipe");
	mini->cmd_list->pid = fork();
	if (mini->cmd_list->pid == -1)
		perror("fork");
	if (mini->cmd_list->pid == 0)
	{
		if (pipex.prev_fd != -1)
		{
			dup2(pipex.prev_fd, STDIN_FILENO);
			close(pipex.prev_fd);
		}
		if (mini->cmd_list->next)
		{
			close(pipex.pipe_fd[0]);
			dup2(pipex.pipe_fd[1], STDOUT_FILENO);
			close(pipex.pipe_fd[1]);
		}
		if (is_out_builtin(mini->cmd_list->args[0]))
			exit(run_builtin(mini->cmd_list, mini));
		child_process(mini->cmd_list, mini);
		executor3(mini, pipex, status);
	}
}

void	executor(t_mini *mini)
{
	t_pipex	pipex;
	int		status;

	pipex.prev_fd = -1;
	while (mini->cmd_list)
	{
		if (is_env_builtin(mini->cmd_list->args[0]) && !mini->cmd_list->next)
			mini->exit_code = run_builtin(mini->cmd_list, mini);
		else
			executor2(mini, pipex, status);
		if (mini->cmd_list->cond_type == AND && mini->exit_code != 0)
			while (mini->cmd_list && mini->cmd_list->cond_type == AND)
				mini->cmd_list = mini->cmd_list->next;
		else if (mini->cmd_list->cond_type == OR && mini->exit_code == 0)
			while (mini->cmd_list && mini->cmd_list->cond_type == OR)
				mini->cmd_list = mini->cmd_list->next;
		else
			mini->cmd_list = mini->cmd_list->next;
	}
	while (wait(NULL) > 0)
		;
}


// ^^LAST ONE
// void	executor(t_mini *mini)
// {
// 	t_pipex	pipex;
// 	int		status;

// 	pipex.prev_fd = -1;
// 	while (mini->cmd_list)
// 	{
// 		if (is_env_builtin(mini->cmd_list->args[0]) && !mini->cmd_list->next)
// 			mini->exit_code = run_builtin(mini->cmd_list, mini);
// 		else
// 		{
// 			if (mini->cmd_list->next)
// 				if (pipe(pipex.pipe_fd) == -1)
// 					perror("pipe");
// 			mini->cmd_list->pid = fork();
// 			if (mini->cmd_list->pid == -1)
// 				perror("fork");
// 			if (mini->cmd_list->pid == 0)
// 			{
// 				if (pipex.prev_fd != -1)
// 				{
// 					dup2(pipex.prev_fd, STDIN_FILENO);
// 					close(pipex.prev_fd);
// 				}
// 				if (mini->cmd_list->next)
// 				{
// 					close(pipex.pipe_fd[0]);
// 					dup2(pipex.pipe_fd[1], STDOUT_FILENO);
// 					close(pipex.pipe_fd[1]);
// 				}
// 				if (is_out_builtin(mini->cmd_list->args[0]))
// 					exit(run_builtin(mini->cmd_list, mini));
// 				child_process(mini->cmd_list, mini);
// 			}
// 			if (pipex.prev_fd != -1)
// 				close(pipex.prev_fd);
// 			if (mini->cmd_list->next)
// 			{
// 				close(pipex.pipe_fd[1]);
// 				pipex.prev_fd = pipex.pipe_fd[0];
// 			}
// 			else
// 				pipex.prev_fd = -1;
// 			waitpid(mini->cmd_list->pid, &status, 0);
// 			mini->exit_code = WEXITSTATUS(status);
// 		}
// 		if (mini->cmd_list->cond_type == AND && mini->exit_code != 0)
// 			while (mini->cmd_list && mini->cmd_list->cond_type == AND)
// 				mini->cmd_list = mini->cmd_list->next;
// 		else if (mini->cmd_list->cond_type == OR && mini->exit_code == 0)
// 			while (mini->cmd_list && mini->cmd_list->cond_type == OR)
// 				mini->cmd_list = mini->cmd_list->next;
// 		else
// 			mini->cmd_list = mini->cmd_list->next;
// 	}
// 	while (wait(NULL) > 0)
// 		;
// }



/* 
int is_builtin(char *cmd)
{
    if (!cmd)
        return (0);
    if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
        || ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
        || ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
        || ft_strcmp(cmd, "exit") == 0)
        return (1);
    return (0);
}

int exec_builtin(t_cmd *cmd, t_mini *mini)
{
    if (ft_strcmp(cmd->args[0], "echo") == 0)
        return (ft_echo(cmd));
    if (ft_strcmp(cmd->args[0], "cd") == 0)
        return (ft_cd(cmd, mini));
    if (ft_strcmp(cmd->args[0], "pwd") == 0)
        return (ft_pwd(cmd));
    if (ft_strcmp(cmd->args[0], "export") == 0)
        return (ft_export(cmd, mini));
    if (ft_strcmp(cmd->args[0], "unset") == 0)
        return (ft_unset(cmd, mini));
    if (ft_strcmp(cmd->args[0], "env") == 0)
        return (ft_env(mini));
    if (ft_strcmp(cmd->args[0], "exit") == 0)
        return (ft_exit(cmd, mini));
    return (1);
}

void    child_process(t_cmd *cmd, t_mini *mini)
{
    int exit_status;

    // 1. Gestionar redirecciones (abrir archivos)
    mng_redirections(cmd);

    // 2. Aplicar redirecciones a STDIN/STDOUT
    if (cmd->fd_in != STDIN_FILENO)
    {
        dup2(cmd->fd_in, STDIN_FILENO);
        close(cmd->fd_in);
    }
    if (cmd->fd_out != STDOUT_FILENO)
    {
        dup2(cmd->fd_out, STDOUT_FILENO);
        close(cmd->fd_out);
    }

    // 3. COMPROBAR SI ES UN BUILT-IN
    // Si lo es, lo ejecutamos y salimos del proceso hijo inmediatamente
    if (is_builtin(cmd->args[0]))
    {
        exit_status = exec_builtin(cmd, mini);
        // Limpieza antes de salir
        free_env_list(mini->env_list);
        free_cmd_list(cmd);
        exit(exit_status);
    }

    // 4. SI NO ES BUILT-IN, BUSCAR BINARIO (Lógica original)
    if (!cmd->cmd_path)
        cmd->cmd_path = get_path(cmd->args[0], mini->env_arr);
    
    if (!cmd->cmd_path)
    {
        write(2, "minishell: command not found: ", 30);
        write(2, cmd->args[0], ft_strlen(cmd->args[0]));
        write(2, "\n", 1);
        free_env_list(mini->env_list);
        free_cmd_list(cmd);
        exit(127);
    }

    // 5. Ejecutar comando externo
    execve(cmd->cmd_path, cmd->args, mini->env_arr);
    perror(cmd->args[0]);
    free_env_list(mini->env_list);
    free_cmd_list(cmd);
    exit(126);
}
 */
