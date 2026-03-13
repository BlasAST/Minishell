/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <andtruji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 01:08:23 by blas              #+#    #+#             */
/*   Updated: 2026/03/13 14:08:25 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// FUNCIONA CORRECTAMENTE

int	ft_unset(t_cmd *cmd, t_mini *mini)
{
	int	i;
	int	exit_st;

	write (1, "Función minishell\n", 19);
	exit_st = 0;
	if (!cmd->args[1])
		return (0);
	i = 1;
	while (cmd->args[i])
	{
		if (!is_valid_unset_id(cmd->args[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(cmd->args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			exit_st = 1;
		}
		else
			remove_env_node(mini, cmd->args[i]);
		i++;
	}
	return (exit_st);
}
