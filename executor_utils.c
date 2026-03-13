/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <andtruji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 01:09:02 by blas              #+#    #+#             */
/*   Updated: 2026/03/13 17:13:50 by andtruji         ###   ########.fr       */
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

static void	open_redir(t_cmd *cmd, t_redir *redir)
{
	if (redir->redir_type == REDIR_IN)
		cmd->fd_in = open(redir->target, O_RDONLY);
	else if (redir->redir_type == REDIR_OUT)
		cmd->fd_out = open(redir->target,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->redir_type == REDIR_APPEND)
		cmd->fd_out = open(redir->target,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
}

int	mng_redirections(t_cmd *cmd, t_pipex *pipex)
{
	t_redir	*redir;

	redir = cmd->redir_list;
	while (redir)
	{
		if (redir->redir_type == REDIR_IN && cmd->fd_in != STDIN_FILENO)
			close(cmd->fd_in);
		if ((redir->redir_type == REDIR_OUT
				|| redir->redir_type == REDIR_APPEND)
			&& cmd->fd_out != STDOUT_FILENO)
			close(cmd->fd_out);
		open_redir(cmd, redir);
		if (cmd->fd_in == -1 || cmd->fd_out == -1)
			return (redir_error(pipex));
		redir = redir->next;
	}
	return (0);
}

void	path_found(t_cmd *cmd, t_mini *mini)
{
	if (cmd->args[0][0] == '\0')
	{
		err_msg("minishell: command not found: ", cmd->args[0], "\n");
		child_exit(mini, 127);
	}
	if (!cmd->cmd_path)
	{
		err_msg("minishell: command not found: ", cmd->args[0], "\n");
		child_exit(mini, 127);
	}
	if (access(cmd->cmd_path, F_OK) != 0)
	{
		err_msg("minishell: ", cmd->cmd_path, ": No such file or directory\n");
		child_exit(mini, 127);
	}
	if (access(cmd->cmd_path, X_OK) != 0)
	{
		err_msg("minishell: ", cmd->cmd_path, ": Permission denied\n");
		child_exit(mini, 126);
	}
	execve(cmd->cmd_path, cmd->args, mini->env_arr);
	perror(cmd->args[0]);
	child_exit(mini, 126);
}
