/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiguenc <bsiguenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 01:08:05 by blas              #+#    #+#             */
/*   Updated: 2026/03/13 12:23:13 by bsiguenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_cmd *cmd, t_mini *mini)
{
	t_env	*temp;

	(void)cmd;
	if (!mini || !mini->env_list)
		return (0);
	temp = mini->env_list;
	while (temp)
	{
		if (temp->value)
		{
			ft_putstr_fd(temp->key, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(temp->value, 1);
			ft_putstr_fd("\n", 1);
		}
		temp = temp->next;
	}
	return (0);
}
