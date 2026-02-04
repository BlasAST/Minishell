#include "../minishell.h"

static int	is_all_digit(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **args, t_mini *mini)
{
	long long	exit_st;

	if (!args[1])
		exit_st = mini->exit_code;
	else
	{
		if (!is_all_digit(args[1]))
		{
			ft_putstr_fd("exit\nminishell: exit: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit_st = 2;
		}
		else if (args[2])
		{
			ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
			return (1);
		}
		else
			exit_st = ft_atoi(args[1]);
	}
	if (!args[2])
		ft_putstr_fd("exit\n", 1);
	free_env_list(mini->env_list);
	// free_mini(mini);
	exit(exit_st % 256);
}