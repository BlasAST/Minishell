/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <andtruji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 01:09:08 by blas              #+#    #+#             */
/*   Updated: 2026/03/19 18:41:01 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes(t_pipex *pipex)
{
	if (pipex->prev_fd != -1)
		close(pipex->prev_fd);
	if (pipex->pipe_fd[0] != -1)
		close(pipex->pipe_fd[0]);
	if (pipex->pipe_fd[1] != -1)
		close(pipex->pipe_fd[1]);
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
	{
		if (pipex->pipe_fd[0] != -1)
			close(pipex->pipe_fd[0]);
		if (pipex->pipe_fd[1] != -1)
			close(pipex->pipe_fd[1]);
		pipex->prev_fd = -1;
	}
}

void	set_values(t_executor *e, t_cmd *cmd)
{
	e->pipex.prev_fd = -1;
	e->pipex.pipe_fd[0] = -1;
	e->pipex.pipe_fd[1] = -1;
	e->cmd = cmd;
	e->prev = NULL;
	e->last_pid = 0;
	e->status = 0;
}

void	set_next(t_executor *e)
{
	e->prev = e->cmd;
	e->cmd = e->cmd->next;
}

void	child_exit(t_mini *mini, int status)
{
	free_all(mini);
	free_env_list(&mini->env_list);
	ft_free_split(mini->env_arr);
	rl_clear_history();
	exit(status);
}
