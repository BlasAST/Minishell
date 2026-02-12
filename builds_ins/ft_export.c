#include "../minishell.h"

// FUNCIONA CORRECTAMENTE

static int	is_valid_id(char *str)
{
	int	i;

	i = 0;
	if (!str || (!ft_isalpha(str[i]) && str[i] != '_'))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	sort_and_print_env(t_env *env)
{
	t_env	*i;
	t_env	*j;
	char	*tmp;

	i = env;
	while (i)
	{
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
		i = i->next;
	}
	i = env;
	while (i)
	{
		printf("declare -x %s", i->key);
		if (i->value)
			printf("=\"%s\"", i->value);
		printf("\n");
		i = i->next;
	}
}

static void	add_to_env(t_mini *mini, char *arg)
{
	char	*key;
	char	*value;
	char	*equal_pos;
	t_env	*new_node;

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
	if (update_env(mini, key, value) == 0) // ->  1
	{
		free(key);
		free(value);
		return ;
	}
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return ;
	new_node->key = key;
	new_node->value = value;
	new_node->next = mini->env_list;
	mini->env_list = new_node;
}

int	ft_export(t_cmd *cmd, t_mini *mini)
{
	int	i;
	int	exit_st;

	write (1, "Función minishell\n", 19);
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