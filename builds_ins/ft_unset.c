/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <andtruji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 01:08:23 by blas              #+#    #+#             */
/*   Updated: 2026/03/13 14:18:40 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_valid_unset_id(char *str)
{
	int	i;

	i = 0;
	if (!str || (!ft_isalpha(str[i]) && str[i] != '_'))
		return (0);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	env_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**env_list_to_arr(t_env *env)
{
	char	**arr;
	char	*tmp;
	int		i;

	arr = malloc(sizeof(char *) * (env_size(env) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->value)
		{
			tmp = ft_strjoin(env->key, "=");
			arr[i] = ft_strjoin(tmp, env->value);
			free(tmp);
		}
		else
			arr[i] = ft_strdup(env->key);
		i++;
		env = env->next;
	}
	arr[i] = NULL;
	return (arr);
}

static void	remove_env_node(t_mini *mini, char *key)
{
	t_env	*current;
	t_env	*prev;

	current = mini->env_list;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev == NULL)
				mini->env_list = current->next;
			else
				prev->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	ft_unset(t_cmd *cmd, t_mini *mini)
{
	int	i;
	int	exit_st;

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
	ft_free_split(mini->env_arr);
	mini->env_arr = env_list_to_arr(mini->env_list);
	return (exit_st);
}
