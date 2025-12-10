#include "minishell.h"

void	expander(t_mini *mini)
{
	t_token	*current;
	char	*temp_str;

	current = mini->token_list;
	while (current)
	{
		if (current->type != HEREDOC)
			expand_token(current, mini);
		if (current->type == WORD)
		{
			temp_str = remove_quotes(current->value);
			free(current->value);
			current->value = temp_str;
		}
		current = current->next;
	}
}