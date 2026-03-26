/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <andtruji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 01:08:54 by blas              #+#    #+#             */
/*   Updated: 2026/03/26 08:56:42 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rerror(char *str, int error_status)
{
	ft_putstr_fd(str, 2);
	exit(error_status);
}

int	sintax_error(char *msg)
{
	write(1, "minishell: syntax error near unexpected token `", 48);
	write(1, msg, ft_strlen(msg));
	write(1, "'\n", 2);
	return (2);
}

int	handle_sintax_error(t_mini *mini)
{
	mini->exit_code = 2;
	free_all(mini);
	return (0);
}

int	handle_heredoc_error(t_mini *mini)
{
	mini->exit_code = 130;
	g_signal_status = 0;
	dup2(open("/dev/tty", O_RDONLY), STDIN_FILENO);
	return (0);
}

void	free_tk(t_token *list, char **tmp)
{
	free_token_list(&list);
	if (*tmp)
		free(*tmp);
}
