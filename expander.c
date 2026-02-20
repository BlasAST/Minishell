#include "minishell.h"

char	*expand_heredoc(char *line, t_mini *mini)
{
	t_env *temp_env;
	char *temp;
	char **temp_split;
	char *new_str;
	char *res;
	int	i;
	int	j;

	temp_env = mini->env_list;
	temp_split = ft_split(line, ' ');
	while (temp_env)
	{
		i = 0;
		j = 0;
		while (temp_split[i])
		{
			while (temp_split[i][j])
			{
				if (temp_split[i][j] == '$')
				{
					new_str = expand_variable((temp_split[i]), &j, mini);
					temp = ft_strjoin(res, new_str);
					free(res);
					free(new_str);
					res = temp;
				}
				else
				{
					temp = ft_substr(&(temp_split[i][j]), i, 1);
					new_str = ft_strjoin(res, temp);
					free(res);
					free(temp);
					res = new_str;
					j++;
				}
			}
			i++;
		}
		temp_env = temp_env->next;
	}
	if (!new_str)
		free(new_str);
	ft_free_split(temp_split);
	return (res);
}

void	expander(t_mini *mini)
{
	t_token	*current;
	char	*temp_str;

	current = mini->token_list;
	while (current)
	{
		if (current->type == WORD)
		{
			if (ft_strchr(current->value, '$'))
			{
				if (!current->prev || current->prev->type != HEREDOC)
					expand_token(mini, current);
			}
			if (ft_strchr(current->value, '\'')
				|| ft_strchr(current->value, '\"'))
			{
				printf("Token Value before removing quotes: %s\n", current->value);
				temp_str = remove_quotes(current->value);
				free(current->value);
				current->value = temp_str;
				printf("Token Value after removing quotes: %s\n", current->value);
			}
		}
		current = current->next;
	}
}
