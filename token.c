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

t_token	*tokenize_input(char *input, t_env *env)
{
	t_token	*list;
	int		i;
	char	*word;

	list = NULL;
	i = 0;
	while (input[i])
	{
		write (1, "Aqui muere el input: ", 20);
		while (input[i] && (input[i] == ' ' || input[i] == '\t'))
			i++;
		if (!input[i])
			break ;
		if (ispecial(&input[i]))
		{
			printf("🧩 [LEXER] Operator token: \"%s\"\n", ft_strndup(&input[i], ispecial(&input[i])));
			add_token(&list, new_token(get_type(&input[i]),
					ft_strndup(&input[i], ispecial(&input[i]))));
			i += ispecial(&input[i]);
		}
		else
		{
			word = parse_word(input, &i);
			if (word && *word)
			{
				printf("🔠 [LEXER] Word token: \"%s\"\n", word);
				add_token(&list, new_token(WORD, word));
				free(word);
			}
			else
				free(word);
		}
	}
	add_token(&list, new_token(END_OF_INPUT, NULL));
	return (list);
}
