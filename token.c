#include "minishell.h"

char	parse_word(char *input, int *i, t_token *list)
{
	int	start;

	start = *i;
	while (input[*i] && input[*i] != ' ' && input[*i] != '\t' && !ispecial(&input[*i]))
		(*i)++;
	add_token(&list, new_token(WORD, ft_strndup(&input[start], *i - start)));
	return (0);
}

void	tokenize_input(char *input, t_env *env)
{
	t_token	*list;
	int		i;

	list = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] && (input[i] == ' ' || input[i] == '\t'))
			i++;
		if (!input[i])
			break ;
		if (ispecial(&input[i]))
		{
			add_token(&list, new_token(get_type(&input[i]), ft_strndup(&input[i], ispecial(&input[i]))));
			i += ispecial(&input[i]);
		}
		else
		{
			add_token(&list, new_token(WORD, ft_strndup(&input[i], 1)));
		}
	}
	
}