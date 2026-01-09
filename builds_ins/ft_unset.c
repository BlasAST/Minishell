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

static void	free_env_node(t_env *node)
{
	if (node->key)
		free(node->key);
	if (node->value)
		free(node->value);
	free(node);
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
			free_env_node(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	ft_unset(char **args, t_mini *mini)
{
	int	i;
	int	exit_st;

	exit_st = 0;
	if (!args[1])
		return (0);
	i = 1;
	while (args[i])
	{
		if (!is_valid_unset_id(args[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			exit_st = 1;
		}
		else
			remove_env_node(mini, args[i]);
		i++;
	}
	return (exit_st);
}