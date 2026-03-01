/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiguenc <bsiguenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 01:07:53 by blas              #+#    #+#             */
/*   Updated: 2026/02/27 13:06:17 by bsiguenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// NO FUNCIONA
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

static char	*get_route_cd(t_cmd *cmd, t_mini *mini)
{
	char	*path;
	char	*env_val;

	path = NULL;
	env_val = NULL;
	if (!cmd->args[1])
	{
		get_value_env(mini->env_list, "HOME", &env_val);
		if (!env_val)
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		else
			path = ft_strdup(env_val);
	}
	else if (ft_strcmp(cmd->args[1], "-") == 0)
	{
		get_value_env(mini->env_list, "OLDPWD", &env_val);
		if (!env_val)
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		else
		{
			path = ft_strdup(env_val);
			printf("%s\n", path);
		}
	}
	else
		path = ft_strdup(cmd->args[1]);
	return (path);
}

int	ft_cd(t_cmd *cmd, t_mini *mini)
{
	char	*value_path;
	char	cwd[4096];

	if (cmd->args[1] && cmd->args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	value_path = get_route_cd(cmd, mini);
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
