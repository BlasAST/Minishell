#include "minishell.h"

void	rerror(char *str, int error_status)
{
	ft_putstr_fd(str, 2);
	exit(error_status);
}
