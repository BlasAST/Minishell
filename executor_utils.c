/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 01:09:02 by blas              #+#    #+#             */
/*   Updated: 2026/03/05 09:45:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
				gp.full = join_path(gp.paths[gp.j], "/", cmd);
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

char	*join_path(char *dir, char *sep, char *cmd)
{
	char	*joined;
	size_t	len;

	if (!dir || !sep || !cmd)
		return (NULL);
	len = ft_strlen(dir) + ft_strlen(sep) + ft_strlen(cmd) + 1;
	joined = malloc(len);
	if (!joined)
		return (NULL);
	ft_strcpy(joined, dir);
	ft_strcat(joined, sep);
	ft_strcat(joined, cmd);
	return (joined);
}

void	mng_redirections(t_cmd *cmd, t_mini *mini)
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
			child_exit(mini, 1);
		}
		redir = redir->next;
	}
}

void	path_found(t_cmd *cmd, t_mini *mini)
{
	if (!cmd->cmd_path)
	{
		write(2, "minishell: command not found: ", 30);
		write(2, cmd->args[0], ft_strlen(cmd->args[0]));
		write(2, "\n", 1);
		child_exit(mini, 127);
	}
	execve(cmd->cmd_path, cmd->args, mini->env_arr);
	perror(cmd->args[0]);
	child_exit(mini, 126);
}
