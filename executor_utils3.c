/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 16:18:50 by andtruji          #+#    #+#             */
/*   Updated: 2026/03/13 16:18:54 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
