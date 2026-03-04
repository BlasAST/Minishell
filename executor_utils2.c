/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <andtruji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 01:09:08 by blas              #+#    #+#             */
/*   Updated: 2026/03/04 12:13:05 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sat_next(t_executor *e)
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
