/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blas <blas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 01:08:08 by blas              #+#    #+#             */
/*   Updated: 2026/02/25 01:10:45 by blas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// SIN FUNCIONAMIENTO

static int	is_all_digit(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_cmd *cmd, t_mini *mini)
{
	long long	exit_st;

	write (1, "Función minishell\n", 19);
	if (cmd->args[1])
	{
		if (!is_all_digit(cmd->args[1]))
		{
			ft_putstr_fd("exit\nminishell: exit: ", 2);
			ft_putstr_fd(cmd->args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(2);
		}
		if (cmd->args[2])
		{
			ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
			return (1);
		}
		exit_st = ft_atoi(cmd->args[1]);
	}
	else
		exit_st = mini->exit_code;
	ft_putstr_fd("exit\n", 1);
	free_all(mini);
	exit(exit_st % 256);
}
