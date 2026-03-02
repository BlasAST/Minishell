/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blas <blas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 01:08:49 by blas              #+#    #+#             */
/*   Updated: 2026/03/02 01:55:19 by blas             ###   ########.fr       */
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
			return (1); // Encontrado
		}
		env = env->next;
	}
	return (0); // No encontrado
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
