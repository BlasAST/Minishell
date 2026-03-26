/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <andtruji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 01:18:35 by blas              #+#    #+#             */
/*   Updated: 2026/03/19 18:50:37 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_heredoc(t_mini *mini)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = mini->cmd_list;
	while (cmd)
	{
		redir = cmd->redir_list;
		while (redir)
		{
			if (redir->redir_type == HEREDOC)
			{
				cmd->fd_in = heredoc(redir->target, mini);
				if (cmd->fd_in == -1)
					return (0);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (1);
}

void	expanding(t_heredoc *hd, t_mini *mini)
{
	hd->expanded = expand_heredoc(hd->line, mini);
	if (hd->expanded)
	{
		write(hd->heredoc[1], hd->expanded, ft_strlen(hd->expanded));
		free(hd->expanded);
	}
}

void	heredoc_loop(t_heredoc *hd, t_mini *mini)
{
	close(hd->heredoc[0]);
	while (1)
	{
		hd->line = readline("heredoc> ");
		if (!hd->line)
		{
			write(2, "\nminishell: warning: here-document delimited by end-of-file (wanted `", 70);
			write(2, hd->clean_lim, ft_strlen(hd->clean_lim));
			write(2, "')\n", 3);
			break ;
		}
		if (ft_strcmp(hd->line, hd->clean_lim) == 0)
		{
			free(hd->line);
			break ;
		}
		if (!hd->quote)
			expanding(hd, mini);
		else
			write(hd->heredoc[1], hd->line, ft_strlen(hd->line));
		write(hd->heredoc[1], "\n", 1);
		free(hd->line);
	}
	close(hd->heredoc[1]);
}

int	heredoc(char *limiter, t_mini *mini)
{
	t_heredoc	hd;

	hd.quote = is_quoted(limiter);
	hd.clean_lim = remove_quotes_1(limiter);
	if (pipe(hd.heredoc) < 0)
		return (perror("pipe"), free(hd.clean_lim), -1);
	hd.pid = fork();
	if (hd.pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		heredoc_loop(&hd, mini);
		free(hd.clean_lim);
		exit(0);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(hd.pid, &hd.status, 0);
	signal(SIGINT, handle_sigint);
	if (WIFSIGNALED(hd.status) && WTERMSIG(hd.status) == SIGINT)
	{
		g_signal_status = 130;
		write(1, "\n", 1);
		return (free(hd.clean_lim), close(hd.heredoc[1]), close(hd.heredoc[0]), -1);
	}
	return (free(hd.clean_lim), close(hd.heredoc[1]), hd.heredoc[0]);
}
