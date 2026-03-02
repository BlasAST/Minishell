/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiguenc <bsiguenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 01:15:12 by blas              #+#    #+#             */
/*   Updated: 2026/02/27 12:56:21 by bsiguenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_cmd *cmd, t_mini *mini, t_pipex *pipex)
{
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
	else if (cmd->next && cmd->cond_type != AND && cmd->cond_type != OR)
	{
		close(pipex->pipe_fd[0]);
		dup2(pipex->pipe_fd[1], STDOUT_FILENO);
		close(pipex->pipe_fd[1]);
	}
	if (!cmd->args || !cmd->args[0])
		child_exit(mini, 0);
	if (cmd->args && is_out_builtin(cmd->args[0]))
		child_exit(mini, run_builtin(cmd, mini));
}

void	executor2(t_mini *mini, t_cmd *cmd, t_pipex *pipex)
{
	if (cmd->next && cmd->cond_type != AND && cmd->cond_type != OR)
		if (pipe(pipex->pipe_fd) == -1)
			perror("pipe");
	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		perror("fork");
		if (cmd->next && cmd->cond_type != AND && cmd->cond_type != OR)
		{
			close(pipex->pipe_fd[0]);
			close(pipex->pipe_fd[1]);
		}
		return ;
	}
	if (cmd->pid == 0)
	{
		mng_redirections(cmd, mini);
		child_process(cmd, mini, pipex);
		if (!cmd->cmd_path)
			cmd->cmd_path = get_path(cmd->args[0], mini->env_arr);
		path_found(cmd, mini);
	}
	else
		close_updt_pipe(cmd, pipex);
}

static void	wait_for_children(t_mini *mini, t_executor *exc)
{
	while ((exc->wpid = wait(&exc->status)) > 0)
	{
		if (exc->wpid == exc->last_pid)
		{
			if (WIFEXITED(exc->status))
				mini->exit_code = WEXITSTATUS(exc->status);
			else if (WIFSIGNALED(exc->status))
				mini->exit_code = 128 + WTERMSIG(exc->status);
		}
	}
}

void	execute_block(t_mini *mini, t_executor *exc)
{
	
	executor2(mini, exc->cmd, &exc->pipex);
	exc->last_pid = exc->cmd->pid;
	wait_for_children(mini, exc);
	exc->prev = exc->cmd;
	exc->cmd = exc->cmd->next;
	
}

void	executor(t_mini *mini)
{
	t_executor	e;

	e.pipex.prev_fd = -1;
	e.pipex.pipe_fd[0] = -1;
	e.pipex.pipe_fd[1] = -1;
	e.cmd = mini->cmd_list;
	e.prev = NULL;
	while (e.cmd)
	{
		if (e.prev && ((e.prev->cond_type == AND && mini->exit_code != 0)
			|| (e.prev->cond_type == OR && mini->exit_code == 0)))
		{
			sat_next(&e);
			continue ;
		}
		if (e.cmd->args && e.cmd->args[0]
			&& is_env_builtin(e.cmd->args[0]))
		{
			mini->exit_code = run_builtin(e.cmd, mini);
			sat_next(&e);
			continue ;
		}
		execute_block(mini, &e);
	}
}
