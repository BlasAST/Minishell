/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blas <blas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 01:20:45 by blas              #+#    #+#             */
/*   Updated: 2026/03/02 02:47:00 by blas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		pw->buf = NULL;
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
		pw->buf = NULL;
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
		if (pw.buf == NULL)
		{
			free(pw.buf);
			return (NULL);
		}
	}
	return (pw.buf);
}

void	tokenation(t_token **list, char *input, int *i)
{
	t_tokenation	tknt;

	tknt.new = NULL;
	if (ispecial(&input[*i]))
	{
		tknt.tmp = ft_strndup(&input[*i], ispecial(&input[*i]));
		tknt.new = new_token(get_type(&input[*i]), tknt.tmp);
		if (!tknt.new)
			return (free_tk(*list, &tknt.tmp)) ;
		add_token(list, tknt.new);
		*i += ispecial(&input[*i]);
		free(tknt.tmp);
	}
	else
	{
		tknt.word = parse_word(input, i);
		if (tknt.word && *tknt.word)
		{
			if (is_wildcard_special(tknt.word))
				tknt.new = new_token(WORD_SPECIAL, tknt.word);
			else
				tknt.new = new_token(WORD, tknt.word);
			if (!tknt.new)
				return (free_tk(*list, &tknt.word)) ;
			add_token(list, tknt.new);
		}
		free(tknt.word);
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
		if (list == NULL && input[i])
			return (NULL);
	}
	add_token(&list, new_token(END_OF_INPUT, NULL));
	return (list);
}
