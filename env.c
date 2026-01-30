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

// int	*get_value_env(t_env *env, char *str, char **send)
// {
// 	char	*temp;

// 	while (env)
// 	{
// 		if (ft_strcmp(env->key, str) == 0)
// 		{
// 			temp = ft_strdup(env->value);
// 			*send = temp;
// 			return (1);
// 		}
// 		env = env->next;
// 	}
// 	return (0);
// }

int	*get_value_env(t_env *env, char *str, char **send)
{
	char	*temp;
	int	*i;

	*i = 1;
	while (env)
	{
		if (ft_strcmp(env->key, str) == 0)
		{
			temp = ft_strdup(env->value);
			*send = temp;
			return (i);
		}
		env = env->next;
	}
	return (0);
}

t_env	*new_env_node(char *str)
{
	t_env	*node;
	int		i;

	node =(t_env *) malloc (sizeof(t_env));
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
