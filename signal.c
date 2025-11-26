#include "minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	write (1, "\n", 1);
}