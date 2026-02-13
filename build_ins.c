#include "minishell.h"

int	is_env_builtin(char *cmd)
{
	return (!ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env"));
}

int	is_out_builtin(char *cmd)
{
	return (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "exit"));
}

int	run_builtin(t_cmd *cmd, t_mini *mini)
{
	static t_builtin	builtins[] = {
	{"echo", ft_echo},
	{"cd", ft_cd},
	{"pwd", ft_pwd},
	{"export", ft_export},
	{"unset", ft_unset},
	{"env", ft_env},
	{"exit", ft_exit},
	{NULL, NULL}
	};
	int					i;

	i = 0;
	while (builtins[i].name)
	{
		if (!ft_strcmp(cmd->args[0], builtins[i].name))
			return (builtins[i].func(cmd, mini));
		i++;
	}
	return (0);
}
