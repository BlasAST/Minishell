#include "../minishell.h"

void	ft_pwd()
{
	char	*buffer;

	buffer = malloc(sizeof(char) * (256));
	if (!buffer)
		return (NULL);
	if (getcwd(buffer,256) != NULL)
		printf("%s", buffer);
	else
		ft_putstr_fd("Error en getcwd", 2);
	free(buffer);
}