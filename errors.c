#include "minishell.h"

void	rerror(char *str, int error_status)
{
	ft_putstr_fd(str, 2);
	exit(error_status);
}

int	sintax_error(char *msg)
{
	write(1, "minishell: syntax error near unexpected token `", 48);
	write(1, msg, ft_strlen(msg));
	write(1, "'\n", 2);
	return (2);
}
