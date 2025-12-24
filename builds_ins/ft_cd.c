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

void	get_route_cd(char	**args, t_mini *mini, char **value_path)
{
	char	*old;

	if (!args[1] && get_value_env(mini->env_list, "HOME", value_path) == 1)
		return ;
	else
		rerror("HOME not set\n", 1);
	if (ft_strcmp(args[1], "-") == 0)
	{
		get_value_env(mini->env_list, "OLDPWD", &old);
		if (ft_strlen(old) == 0)
		{
			printf("minishell: cd: OLDPWD not set\n");
			free(old);
			return (NULL);
		}
		printf("%s", old);
		return (old);
	}
	return (ft_strdup(args[1]));
}

void	ft_cd(char	**args, t_mini *mini)
{
	char	*value_path;
	char	cwd[4096];

	if (args[1] && args[2])
		rerror("Too many args", 1);
	get_route_cd(args, mini, &value_path);
	if (!value_path)
		return (1);
	if (getcwd(cwd, 4096))
		update_env(mini, "OLDPWD", cwd);
	if (chdir(value_path) == -1)
	{
		free(value_path);
		perror("minishell: cd");
		return (1);
	}
	if (getcwd(cwd, 4096))
		update_env(mini, "PWD", cwd);
	free(value_path);
}