/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <andtruji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 01:09:02 by blas              #+#    #+#             */
/*   Updated: 2026/02/25 11:50:04 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	is_and_or(t_cmd **cmd, t_mini *mini)
{
	while (cmd && *cmd && (*cmd)->next && (*cmd)->cond_type != AND && (*cmd)->cond_type != OR)
		cmd = &(*cmd)->next;
	if (cmd && *cmd && ((*cmd)->cond_type == AND && mini->exit_code != 0)
			|| ((*cmd)->cond_type == OR && mini->exit_code == 0))
	{
		cmd = &(*cmd)->next;
		while (cmd && *cmd && (*cmd)->cond_type != END_OF_INPUT)
		{
			if ((*cmd)->cond_type == AND || (*cmd)->cond_type == OR)
				break ;
			cmd = &(*cmd)->next;
		}
	}
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
		write(2, cmd->args[0], ft_strlen(cmd->args[0]));
		write(2, "\n", 1);
		exit(127);
	}
	execve(cmd->cmd_path, cmd->args, mini->env_arr);
	perror(cmd->args[0]);
	exit(126);
}
