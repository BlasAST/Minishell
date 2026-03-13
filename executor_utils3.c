/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <andtruji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 16:18:50 by andtruji          #+#    #+#             */
/*   Updated: 2026/03/13 17:11:36 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err_msg(char *s1, char *s2, char *s3)
{
	write(2, s1, ft_strlen(s1));
	write(2, s2, ft_strlen(s2));
	write(2, s3, ft_strlen(s3));
}

void	wait_for_children(t_mini *mini, t_executor *e)
{
	waitpid(e->last_pid, &e->status, 0);
	if (WIFEXITED(e->status))
		mini->exit_code = WEXITSTATUS(e->status);
	else if (WIFSIGNALED(e->status))
		mini->exit_code = 128 + WTERMSIG(e->status);
}

int	redir_error(t_pipex *pipex)
{
	perror("Redirection error");
	close_pipes(pipex);
	return (1);
}

int	is_subshell(t_cmd *cmd, t_mini *mini)
{
	if (cmd->ishell)
	{
		executor(cmd->subshell, mini);
		child_exit(mini, mini->exit_code);
		return (1);
	}
	return (0);
}

void	close_cmd_fds(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->fd_in != STDIN_FILENO)
		{
			close(cmd->fd_in);
			cmd->fd_in = STDIN_FILENO;
		}
		if (cmd->fd_out != STDOUT_FILENO)
		{
			close(cmd->fd_out);
			cmd->fd_out = STDOUT_FILENO;
		}
		cmd = cmd->next;
	}
}
