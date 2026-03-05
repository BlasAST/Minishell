/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 01:20:39 by blas              #+#    #+#             */
/*   Updated: 2026/03/05 09:24:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_word(t_tokenation *tknt, char *input, int *i, t_token **list)
{
	tknt->word = parse_word(input, i);
	if (tknt->word && *tknt->word)
	{
		if (is_wildcard_special(tknt->word))
			tknt->new = new_token(WORD_SPECIAL, tknt->word);
		else
			tknt->new = new_token(WORD, tknt->word);
		if (!tknt->new)
			return (free_tk(*list, &tknt->word));
		add_token(list, tknt->new);
	}
	free(tknt->word);
}

t_token	*new_token(t_token_type type, char *value)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = type;
	new->value = NULL;
	if (value)
	{
		new->value = ft_strdup(value);
		if (!new->value)
		{
			free(new);
			return (NULL);
		}
	}
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	add_token(t_token **list, t_token *new)
{
	t_token	*temp;

	if (new == NULL)
		return ;
	if (!list || *list == NULL)
	{
		*list = new;
		return ;
	}
	temp = *list;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
}

t_token_type	get_type(char *s)
{
	if (!ft_strncmp(s, "&&", 2))
		return (AND);
	if (!ft_strncmp(s, "||", 2))
		return (OR);
	if (!ft_strncmp(s, "<<", 2))
		return (HEREDOC);
	if (!ft_strncmp(s, ">>", 2))
		return (REDIR_APPEND);
	if (!ft_strncmp(s, "<", 1))
		return (REDIR_IN);
	if (!ft_strncmp(s, ">", 1))
		return (REDIR_OUT);
	if (!ft_strncmp(s, "|", 1))
		return (PIPE);
	if (!ft_strncmp(s, "(", 1))
		return (LPAREN);
	if (!ft_strncmp(s, ")", 1))
		return (RPAREN);
	return (WORD);
}

int	ispecial(char *c)
{
	if (!ft_strncmp(c, ">>", 2) || !ft_strncmp(c, "<<", 2)
		|| !ft_strncmp(c, "&&", 2) || !ft_strncmp(c, "||", 2))
		return (2);
	if (*c == '|' || *c == '<' || *c == '>' || *c == '(' || *c == ')')
		return (1);
	return (0);
}
