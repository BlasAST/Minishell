/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiguenc <bsiguenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 02:17:22 by blas              #+#    #+#             */
/*   Updated: 2026/02/27 14:06:49 by bsiguenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_shlvl(t_mini *mini)
{
	char	*shlvl_str;
	char	*new_shlvl_str;
	int		shlvl_num;
	// int		*i;

	shlvl_str = NULL;
	// i = get_value_env(mini->env_list, "SHLVL", &shlvl_str);
	// if (shlvl_str)
	if (get_value_env(mini->env_list, "SHLVL", &shlvl_str))
	{
		shlvl_num = ft_atoi(shlvl_str) + 1;
		new_shlvl_str = ft_itoa(shlvl_num);
		free(shlvl_str);
	}
	else
		new_shlvl_str = ft_strdup("1");
	update_env(mini, "SHLVL", new_shlvl_str);
	free(new_shlvl_str);
	// free(i);
}

// static int	env_list_size(t_env *env_list)
// {
// 	int	i;

// 	i = 0;
// 	while (env_list)
// 	{
// 		i++;
// 		env_list = env_list->next;
// 	}
// 	return (i);
// }
/* 
void	update_env_arr(t_mini *mini)
{
	t_env	*temp;
	char	*temp_str;
	int		i;

	mini->env_arr = malloc(sizeof(char *)
			* (env_list_size(mini->env_list) + 1));
	if (!mini->env_arr)
		return ;
	temp = mini->env_list;
	i = 0;
	while (temp)
	{
		temp_str = ft_strjoin(temp->key, "=");
		if (temp->value)
			mini->env_arr[i] = ft_strjoin(temp_str, temp->value);
		else
			mini->env_arr[i] = ft_strdup(temp_str);
		free(temp_str);
		temp = temp->next;
		i++;
	}
	mini->env_arr[i] = NULL;
} */
