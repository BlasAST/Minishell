/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blas <blas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 02:17:22 by blas              #+#    #+#             */
/*   Updated: 2026/03/02 01:57:22 by blas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env_arr(t_mini *mini)
{
	int		i;
	char	*temp;
	char	*full;
	int		val_temp;

	i = 0;
	while (mini->env_arr[i] != NULL)
	{
		if (ft_strncmp(mini->env_arr[i], "SHLVL=", 6) == 0)
		{
			temp = ft_substr(mini->env_arr[i], 6, ft_strlen(mini->env_arr[i]));
			val_temp = ft_atoi(temp) + 1;
			free(temp);
			temp = ft_itoa(val_temp);
			full = ft_strjoin("SHLVL=", temp);
			free(temp);
			free(mini->env_arr[i]);
			mini->env_arr[i] = full;
			return ;
		}
		i++;
	}
}

void	update_shlvl(t_mini *mini)
{
	char	*shlvl_str;
	char	*new_shlvl_str;
	int		shlvl_num;

	shlvl_str = NULL;
	if (get_value_env(mini->env_list, "SHLVL", &shlvl_str))
	{
		shlvl_num = ft_atoi(shlvl_str) + 1;
		new_shlvl_str = ft_itoa(shlvl_num);
		free(shlvl_str);
	}
	else
		new_shlvl_str = ft_strdup("1");
	update_env(mini, "SHLVL", new_shlvl_str);
	update_env_arr(mini);
	free(new_shlvl_str);
}

void	get_envp(t_mini *mini, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
		i++;
	mini->env_arr = malloc (sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i] != NULL)
	{
		mini->env_arr[i] = ft_strdup(envp[i]);
		i++;
	}
	mini->env_arr[i] = NULL;
}
