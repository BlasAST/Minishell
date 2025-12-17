#include "minishell.h"

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
				if (!current->prev ||  current->prev->type != HEREDOC)
					expand_token(mini, current);
			}
			if (ft_strchr(current->value, '\'') || ft_strchr(current->value, '\"'))
			{
				temp_str =  remove_quotes(current->value);
				free(current->value);
				current->value = temp_str;
			}
		}
		current = current->next;
	}
}