#include "minishell.h"

void	parse_word3(char *input, int *i, t_parse_word *pw)
{
	pw->start = *i;
	while (input[*i] && !ispecial(&input[*i]) && input[*i] != ' '
		&& input[*i] != '\t')
		(*i)++;
	pw->segment = ft_strndup(&input[pw->start], *i - pw->start);
	pw->tmp = pw->buf;
	pw->buf = malloc(ft_strlen(pw->tmp) + ft_strlen(pw->segment) + 1);
	if (pw->buf == NULL)
	{
		free(pw->tmp);
		free(pw->segment);
		return ;
	}
	ft_strcpy(pw->buf, pw->tmp);
	ft_strcat(pw->buf, pw->segment);
	free(pw->tmp);
	free(pw->segment);
}

void	parse_word1(char *input, int *i, t_parse_word *pw)
{
	pw->quote = input[*i];
	pw->start = *i;
	(*i)++;
	while (input[*i] && input[*i] != pw->quote)
		(*i)++;
	if (input[*i] == pw->quote)
		(*i)++;
	pw->segment = ft_strndup(&input[pw->start], *i - pw->start);
	pw->tmp = pw->buf;
	pw->buf = malloc(ft_strlen(pw->tmp) + ft_strlen(pw->segment) + 1);
	if (pw->buf == NULL)
	{
		free(pw->tmp);
		free(pw->segment);
		return ;
	}
	ft_strcpy(pw->buf, pw->tmp);
	ft_strcat(pw->buf, pw->segment);
	free(pw->tmp);
	free(pw->segment);
}

char	*parse_word(char *input, int *i)
{
	t_parse_word	pw;

	pw.buf = ft_calloc(1, 1);
	pw.start = *i;
	while (input[*i] && input[*i] != ' '
		&& input[*i] != '\t' && !ispecial(&input[*i]))
	{
		if (input[*i] == '\'' || input[*i] == '\"')
			parse_word1(input, i, &pw);
		else
			parse_word3(input, i, &pw);
	}
	return (pw.buf);
}

void	tokenation(t_token **list, char *input, int *i)
{
	char	*word;

	if (ispecial(&input[*i]))
	{
		add_token(list, new_token(get_type(&input[*i]),
				ft_strndup(&input[*i], ispecial(&input[*i]))));
		*i += ispecial(&input[*i]);
	}
	else
	{
		word = parse_word(input, i);
		if (word && *word)
			add_token(list, new_token(WORD, word));
		free(word);
	}
}

t_token	*tokenize_input(char *input)
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
		tokenation(&list, input, &i);
	}
	add_token(&list, new_token(END_OF_INPUT, NULL));
	return (list);
}
