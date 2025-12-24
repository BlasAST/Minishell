#include "../minishell.h"

void	ft_env(t_env *temp)
{
	while (temp)
	{
		printf("%s", temp->value);
		temp = temp->next;
	}
}
