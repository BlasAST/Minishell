#include "../minishell.h"

void	ft_echo(char *val)
{
	printf("Hola no");
	write(1, val, ft_strlen(val));
}