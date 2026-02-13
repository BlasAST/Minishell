#include "../minishell.h"

int	ft_pwd(t_cmd *cmd, t_mini *mini)
{
	char	cwd[4096];
 
	(void)cmd;
	(void)mini;
	write (1, "Función minishell\n", 19);
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