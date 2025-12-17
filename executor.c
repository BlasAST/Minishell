#include "minishell.h"

void    heredoc(t_cmd *cmd)
{
    int     heredoc[2];
    char    *limiter;
    char    *line;

    if (pipe(heredoc) < 0)
        perror("pipe");
    while (1)
    {
        line = readline("heredoc> ");
        if (!line || ft_strcmp(line, limiter) == 0)
        {
            break ;
            free(line); 
        }
            break ;
        write(heredoc[1], line , ft_strlen(line));
        free(line);
    }

}

void    mng_redirections(t_cmd * cmd)
{
    t_redir    *redir;

    redir = cmd->redir_list;
    while (redir)
    {
        if (redir->redir_type == REDIR_IN)
            cmd->fd_in = open(redir->target, O_RDONLY);
        else if (redir->redir_type == REDIR_OUT)
            cmd->fd_out = open(redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        else if (redir->redir_type == REDIR_APPEND)
            cmd->fd_out = open(redir->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
        else if (redir->redir_type == HEREDOC)
            cmd->fd_in = heredoc(redir->target);
        if (cmd->fd_in == -1 || cmd->fd_out == -1)
        {
            perror("redirection error");
            exit(EXIT_FAILURE);
        }
        redir = redir->next;
    }
}

void    child_process(t_cmd *cmd, t_mini *mini)
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
}

int execute_command(t_cmd *cmd, t_mini *mini)
{
    
        child_process(cmd, mini);
}

void    executor(t_cmd *cmd_list, t_mini *mini)
{
    t_pipex pipex;

    pipex.prev_fd = -1;
    while (cmd_list)
    {
        if (cmd_list->next)
            pipe(pipex.pipe_fd);
        cmd_list->pid = fork();
        if (cmd_list->pid == 0)
        {
            if (pipex.prev_fd != -1)
            {
                dup2(pipex.prev_fd, STDIN_FILENO);
                close(pipex.prev_fd);
            }
            if (cmd_list->next)
            {
                close(pipex.pipe_fd[0]);
                dup(pipex.pipe_fd[1], STDOUT_FILENO);
                close(pipex.pipe_fd[1]);
            }
            child_process(cmd_list, mini);
            exit(execute_command(cmd_list, mini));
        }
        if (pipex.prev_fd != -1)
            close(pipex.prev_fd);
        if (cmd_list->next)
        {
            close(pipex.pipe_fd[1]);
            pipex.prev_fd = pipex.pipe_fd[0];
        }
        cmd_list = cmd_list->next;
    }
    while (wait(&status) > 0)
        mini->exit_code = WEXITSTATUS(status);
}