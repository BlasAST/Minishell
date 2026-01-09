#include "../minishell.h"

int	ft_pwd(void)
{
	char	cwd[4096];

	if (getcwd(cwd, 4096) != NULL)
	{
		ft_putstr_fd(cwd, 1);
		ft_putstr_fd("\n", 1);
		return (0);
	}
	else
	{
		perror("minishell: pwd");
		return (1);
	}
}