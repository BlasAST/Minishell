/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blas <blas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 01:16:55 by blas              #+#    #+#             */
/*   Updated: 2026/02/25 01:18:20 by blas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*new;

	if (!s1 || !s2)
		return (NULL);
	new = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (new);
}

char	*expand_heredoc(char *line, t_mini *mini)
{
	char	**temp_split;
	char	*new_str;
	char	*temp;
	char	*res;
	int		i;
	int		j;

	if (!line)
		return (NULL);
	res = ft_strdup("");
	temp_split = ft_split(line, ' ');
	i = 0;
	while (temp_split[i])
	{
		j = 0;
		while (temp_split[i][j])
		{
			if (temp_split[i][j] == '$')
			{
				new_str = expand_variable(temp_split[i], &j, mini);
				res = ft_strjoin_free(res, new_str);
			}
			else
			{
				temp = ft_substr(temp_split[i], j, 1);
				res = ft_strjoin_free(res, temp);
				j++;
			}
		}
		if (temp_split[i + 1])
			res = ft_strjoin_free(res, ft_strdup(" "));
		i++;
	}
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
			if ((ft_strchr(current->value, '\'')
				|| ft_strchr(current->value, '\"'))
				&& (!current->prev || current->prev->type != HEREDOC))
			{
				temp_str = remove_quotes(current->value);
				free(current->value);
				current->value = temp_str;
			}
		}
		current = current->next;
	}
}
