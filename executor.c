/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 16:19:02 by andtruji          #+#    #+#             */
/*   Updated: 2026/03/13 16:19:15 by andtruji         ###   ########.fr       */
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
		dup2(pipex->prev_fd, STDIN_FILENO);
	if (cmd->fd_out != STDOUT_FILENO)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
	else if (cmd->next && pipex->pipe_fd[1] != -1)
		dup2(pipex->pipe_fd[1], STDOUT_FILENO);
	close_pipes(pipex);
	if (!cmd->args || !cmd->args[0])
		child_exit(mini, 0);
	if (cmd->args && (is_out_builtin(cmd->args[0])
			|| is_env_builtin(cmd->args[0])))
		child_exit(mini, run_builtin(cmd, mini));
}

void	children(t_cmd *cmd, t_mini *mini, t_pipex *pipex)
{
	if (cmd->pid == 0)
	{
		if (is_subshell(cmd, mini))
			return ;
		if (mng_redirections(cmd, pipex))
			child_exit(mini, 1);
		child_process(cmd, mini, pipex);
		if (!cmd->cmd_path)
			cmd->cmd_path = get_path(cmd->args[0], mini->env_arr);
		path_found(cmd, mini);
	}
	else
		close_updt_pipe(cmd, pipex);
}

void	executor2(t_mini *mini, t_cmd *cmd, t_pipex *pipex)
{
	if (cmd->next && cmd->fd_out == STDOUT_FILENO
		&& cmd->cond_type != AND && cmd->cond_type != OR)
	{
		if (pipe(pipex->pipe_fd) == -1)
			perror("pipe");
	}
	else
	{
		pipex->pipe_fd[0] = -1;
		pipex->pipe_fd[1] = -1;
	}
	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		perror("fork");
		if (cmd->next && cmd->cond_type != AND && cmd->cond_type != OR)
			close_pipes(pipex);
		return ;
	}
	children(cmd, mini, pipex);
}

void	execute_block(t_mini *mini, t_executor *e)
{
	executor2(mini, e->cmd, &e->pipex);
	e->last_pid = e->cmd->pid;
	wait_for_children(mini, e);
	e->prev = e->cmd;
	e->cmd = e->cmd->next;
}

void	executor(t_cmd *cmd, t_mini *mini)
{
	t_executor	e;

	set_values(&e, cmd);
	while (e.cmd)
	{
		if (e.prev && ((e.prev->cond_type == AND && mini->exit_code != 0)
				|| (e.prev->cond_type == OR && mini->exit_code == 0)))
		{
			set_next(&e);
			continue ;
		}
		if (e.cmd->args && e.cmd->args[0]
			&& is_env_builtin(e.cmd->args[0]))
		{
			if ((!e.cmd->next || (e.cmd->cond_type == AND
						|| e.cmd->cond_type == OR))
				&& e.pipex.prev_fd == -1)
			{
				mini->exit_code = run_builtin(e.cmd, mini);
				set_next(&e);
				continue ;
			}
		}
		execute_block(mini, &e);
	}
}
