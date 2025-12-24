#include "../minishell.h"

void	ft_echo(char *value)
{
	write(1, value, ft_strlen(value));
}