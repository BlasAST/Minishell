#include "minishell.h"

void	handle_siging(int sig)
{
	(void)sig;
	write (1, "\n", 1);
}