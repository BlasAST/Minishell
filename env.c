#include "minishell.h"

// File for things related to the environment

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
