#include "minishell.h"

void	free_env_list(t_env *env_list)
{
	t_env	*tmp;

	while (env_list)
	{
		tmp = env_list->next;
		free(env_list->key);
		if (env_list->value)
			free (env_list->value);
		free(env_list);
		env_list = tmp;
	}
}

void	free_token_list(t_token *list)
{
	t_token	*tmp;

	while (list)
	{
		tmp = list->next;
		if (list->value)
			free(list->value);
		free(list);
		list = tmp;
	}
}

void	free_redir_list(t_redir *list)
{
	t_redir	*tmp;

	while (list)
	{
		tmp = list->next;
		if (list->target)
			free(list->target);
		free(list);
		list = tmp;
	}
}

void	free_cmd_list(t_cmd *list)
{
	t_cmd	*tmp;
	int		i;

	while (list)
	{
		tmp = list->next;
		if (list->args)
		{
			i = 0;
			while (list->args[i])
				free(list->args[i++]);
			free(list->args);
		}
		if (list->cmd_path)
			free(list->cmd_path);
		if (list->redir_list)
			free_redir_list(list->redir_list);
		free(list);
		list = tmp;
	}
}

void	free_all(t_mini *mini)
{
	if (mini->token_list)
		free_token_list(mini->token_list);
	if (mini->cmd_list)
		free_cmd_list(mini->cmd_list);
	mini->token_list = NULL;
	mini->cmd_list = NULL;
}
