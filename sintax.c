#include "minishell.h"

int	check_sintax(t_token *token_list)
{
	if (!token_list)
		return (0);
	if (token_list->type == PIPE)
		return (sintax_error("|"));
	while (token_list && token_list->next)
	{
		if (token_list->type == PIPE && token_list->next->type == PIPE)
			return (sintax_error("|"));
		if (token_list->type == AND || token_list->type == OR)
			if (token_list->prev != WORD || token_list->next != WORD)
				return (0);
		if (token_list->type == REDIR_IN || token_list->type == REDIR_OUT
			|| token_list->type == REDIR_APPEND || token_list->type == HEREDOC)
				if (!token_list->next || token_list->next->type != WORD)
					return (sintax_error("newline"));
		token_list = token_list->next;
	}
	if (token_list->type == PIPE)
		return (sintax_error("|"));
	return (1);
}
