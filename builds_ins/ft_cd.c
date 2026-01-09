#include "../minishell.h"

int	update_env(t_mini *mini, char *key, char *value)
{
	t_env	*temp;
	char	*new_val;

	temp = mini->env_list;
	new_val = ft_strdup(value);
	if (!new_val)
		return (1);
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
		{
			free(temp->value);
			temp->value = new_val;
			return (0);
		}
		temp = temp->next;
	}
	free(new_val);
	return (1);
}

char	*get_route_cd(char **args, t_mini *mini)
{
	char	*path;

	path = NULL;
	if (!args[1])
	{
		if (get_value_env(mini->env_list, "HOME", &path) == 0 || !path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (NULL);
		}
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		if (get_value_env(mini->env_list, "OLDPWD", &path) == 0 || !path)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			return (NULL);
		}
		printf("%s\n", path);
	}
	else
		path = ft_strdup(args[1]);
	return (path);
}

int	ft_cd(char **args, t_mini *mini)
{
	char	*value_path;
	char	cwd[4096];

	if (args[1] && args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	value_path = get_route_cd(args, mini);
	if (!value_path)
		return (1);
	if (getcwd(cwd, 4096))
		update_env(mini, "OLDPWD", cwd);
	if (chdir(value_path) == -1)
	{
		perror("minishell: cd");
		free(value_path);
		return (1);
	}
	if (getcwd(cwd, 4096))
		update_env(mini, "PWD", cwd);
	free(value_path);
	return (0);
}