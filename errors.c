/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blas <blas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 01:08:54 by blas              #+#    #+#             */
/*   Updated: 2026/02/25 01:08:55 by blas             ###   ########.fr       */
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

int	handle_sintax_error(t_mini *mini, char *input)
{
	mini->exit_code = 258;
	free_all(mini);
	free(input);
	return (0);
}

int	handle_heredoc_error(t_mini *mini, char *input)
{
	mini->exit_code = 130;
	free_all(mini);
	free(input);
	return (0);
}
