/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blas <blas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 02:45:38 by blas              #+#    #+#             */
/*   Updated: 2026/03/09 16:35:56 by blas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_wildcard_special(char *word)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (word[i])
	{
		if ((word[i] == '\'' || word[i] == '\"') && !quote)
			quote = word[i];
		else if (word[i] == quote)
			quote = 0;
		else if (word[i] == '*' && !quote)
			return (1);
		i++;
	}
	return (0);
}

static void	insert_wildcard_matches(t_token *current, char **matches, int count)
{
	int		i;
	t_token	*temp_next;
	t_token	*new_node;

	temp_next = current->next;
	i = 1;
	while (i < count)
	{
		new_node = malloc(sizeof(t_token));
		if (!new_node)
			return ;
		new_node->value = ft_strdup(matches[i]);
		new_node->type = WORD;
		new_node->prev = current;
		current->next = new_node;
		current = new_node;
		i++;
	}
	current->next = temp_next;
	if (temp_next)
		temp_next->prev = current;
}

void	expand_asterisk_token(t_mini *mini, t_token *current)
{
	int		count;
	char	**matches;

	(void)mini;
	count = count_matches(current->value);
	if (count == 0)
	{
		current->type = WORD;
		return ;
	}
	matches = get_wildcard_matches(current->value, count);
	if (!matches)
		return ;
	free(current->value);
	current->value = ft_strdup(matches[0]);
	current->type = WORD;
	insert_wildcard_matches(current, matches, count);
	ft_free_split(matches);
}

/* void	expand_asterisk_token(t_mini *mini, t_token *current)
{
	int		count;
	char	**matches;
	int		i;
	t_token	*temp_next;
	t_token	*new_node;

	(void)mini;
	count = count_matches(current->value);
	if (count == 0)
	{
		current->type = WORD;
		return ;
	}
	matches = get_wildcard_matches(current->value, count);
	if (!matches)
		return ;
	free(current->value);
	current->value = ft_strdup(matches[0]);
	current->type = WORD;
	temp_next = current->next;
	i = 1;
	while (i < count)
	{
		new_node = malloc(sizeof(t_token));
		new_node->value = ft_strdup(matches[i]);
		new_node->type = WORD;
		current->next = new_node;
		current = new_node;
		i++;
	}
	current->next = temp_next;
	if (temp_next)
		temp_next->prev = current;
	ft_free_split(matches);
} */
