/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <andtruji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 16:19:02 by andtruji          #+#    #+#             */
/*   Updated: 2026/03/19 18:41:18 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_cmd *cmd, t_pipex *pipex)
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
	else if (cmd->next && pipex->pipe_fd[1] != -1)
	{
		dup2(pipex->pipe_fd[1], STDOUT_FILENO);
		close(pipex->pipe_fd[1]);
	}
	close_pipes(pipex);
}

void	children(t_cmd *cmd, t_mini *mini, t_executor *e)
{
	if (cmd->pid == 0)
	{
		child_signals();
		if (is_subshell(cmd, mini))
			child_exit(mini, 0);
		if (mng_redirections(cmd, &e->pipex))
			child_exit(mini, 1);
		child_process(cmd, &e->pipex);
		if (!cmd->args || !cmd->args[0])
			child_exit(mini, 0);
		if (cmd->args && (is_out_builtin(cmd->args[0])
				|| is_env_builtin(cmd->args[0])))
			child_exit(mini, run_builtin(cmd, mini));
		if (!cmd->cmd_path)
			cmd->cmd_path = get_path(cmd->args[0], mini->env_arr);
		path_found(cmd, mini);
	}
	else
		close_updt_pipe(cmd, &e->pipex);
}

void	executor2(t_mini *mini, t_cmd *cmd, t_executor *e)
{
	if (cmd->next && cmd->fd_out == STDOUT_FILENO
		&& cmd->cond_type != AND && cmd->cond_type != OR)
	{
		if (pipe(e->pipex.pipe_fd) == -1)
			perror("pipe");
	}
	else
	{
		e->pipex.pipe_fd[0] = -1;
		e->pipex.pipe_fd[1] = -1;
	}
	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		perror("fork");
		if (cmd->next && cmd->cond_type != AND && cmd->cond_type != OR)
		close_pipes(&e->pipex);
		return ;
	}
	children(cmd, mini, e);
}

void	execute_block(t_mini *mini, t_executor *e)
{
	executor2(mini, e->cmd, e);
	e->last_pid = e->cmd->pid;
	e->prev = e->cmd;
	e->cmd = e->cmd->next;
	close_cmd_fds(mini->cmd_list);
}

void	executor(t_cmd *cmd, t_mini *mini)
{
	t_executor	e;

	set_values(&e, cmd);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
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
	wait_for_children(mini, &e);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_DFL);
}
