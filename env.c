/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blas <blas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 01:08:49 by blas              #+#    #+#             */
/*   Updated: 2026/03/09 13:13:54 by blas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// File for things related to the environment

int	find_path(t_env *env, char *str)
{
	while (env)
	{
		if (ft_strcmp(env->key, str) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

int	get_value_env(t_env *env, char *str, char **send)
{
	while (env)
	{
		if (ft_strcmp(env->key, str) == 0)
		{
			if (env->value)
				*send = ft_strdup(env->value);
			else
				*send = NULL;
			return (1);
		}
		env = env->next;
	}
	return (0);
}

char	*get_env_val(t_env *env, char *key)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (ft_strlen(key) == ft_strlen(temp->key)
			&& ft_strncmp(temp->key, key, ft_strlen(key)) == 0)
			return (ft_strdup(temp->value));
		temp = temp->next;
	}
	return (ft_strdup(""));
}

t_env	*new_env_node(char *str)
{
	t_env	*node;
	int		i;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	node->key = ft_substr(str, 0, i);
	if (str[i] == '=')
		node->value = ft_strdup(str + i + 1);
	else
		node->value = NULL;
	node->next = NULL;
	return (node);
}
