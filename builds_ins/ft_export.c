/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <andtruji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 01:08:11 by blas              #+#    #+#             */
/*   Updated: 2026/03/13 14:20:19 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*get_next(t_env *i)
{
	t_env	*j;
	char	*tmp;

	j = i->next;
	while (j)
	{
		if (ft_strcmp(i->key, j->key) > 0)
		{
			tmp = i->key;
			i->key = j->key;
			j->key = tmp;
			tmp = i->value;
			i->value = j->value;
			j->value = tmp;
		}
		j = j->next;
	}
	return (i->next);
}

static void	sort_and_print_env(t_env *env)
{
	t_env	*i;

	i = env;
	while (i)
		i = get_next(i);
	i = env;
	while (i)
	{
		write(1, "declare -x ", 11);
		write(1, i->key, ft_strlen(i->key));
		if (i->value)
		{
			write(1, "=\"", 2);
			write(1, i->value, ft_strlen(i->value));
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		i = i->next;
	}
}

static void	new_nodes(char *key, char *value, t_mini *mini)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return ;
	new_node->key = key;
	new_node->value = value;
	new_node->next = mini->env_list;
	mini->env_list = new_node;
}

static void	add_to_env(t_mini *mini, char *arg)
{
	char	*key;
	char	*value;
	char	*equal_pos;

	equal_pos = ft_strchr(arg, '=');
	if (equal_pos)
	{
		key = ft_substr(arg, 0, equal_pos - arg);
		value = ft_strdup(equal_pos + 1);
	}
	else
	{
		key = ft_strdup(arg);
		value = NULL;
	}
	if (update_env(mini, key, value) == 0)
	{
		free(key);
		free(value);
		return ;
	}
	new_nodes(key, value, mini);
}

int	ft_export(t_cmd *cmd, t_mini *mini)
{
	int	i;
	int	exit_st;

	exit_st = 0;
	if (!cmd->args[1])
	{
		sort_and_print_env(mini->env_list);
		return (0);
	}
	i = 1;
	while (cmd->args[i])
	{
		if (!is_valid_id(cmd->args[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(cmd->args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			exit_st = 1;
		}
		else
			add_to_env(mini, cmd->args[i]);
		i++;
	}
	return (exit_st);
}
