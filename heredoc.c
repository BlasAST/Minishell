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

static char	*remove_quotes_1(char *str)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = malloc(ft_strlen(str) + 1);
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
			res[j++] = str[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}

int	is_quoted(char *limiter)
{
	while (*limiter)
	{
		if (*limiter == '\'' || *limiter == '\"')
			return (1);
		limiter++;
	}
	return (0);
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

int	heredoc(char *limiter, t_mini *mini)
{
	t_heredoc	hd;

	hd.quote = is_quoted(limiter);
	hd.clean_lim = remove_quotes_1(limiter);
	hd.expanded = NULL;
	if (pipe(hd.heredoc) < 0)
		return (perror("pipe"), -1);
	while (1)
	{
		hd.line = readline("heredoc> ");
		if (!hd.line || ft_strcmp(hd.line, hd.clean_lim) == 0)
		{
			free(hd.line);
			break ;
		}
		add_history(hd.line);
		if (!hd.quote)
			expanding(&hd, mini);
		else
			write(hd.heredoc[1], hd.line, ft_strlen(hd.line));
		write(hd.heredoc[1], "\n", 1);
		free(hd.line);
	}
	return (free(hd.clean_lim), close(hd.heredoc[1]), hd.heredoc[0]);
}
