/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blas <blas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 18:47:25 by blas              #+#    #+#             */
/*   Updated: 2026/02/25 01:16:50 by blas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_expansible(char *str)
{
	if ((ft_isalpha(*str) || *str == '_' || *str == '?'))
		return (1);
	return (0);
}

char	*remove_quotes(char *str)
{
	char	*new;
	int		i;
	int		j;
	char	status;

	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	i = 0;
	j = 0;
	status = 0;
	while (str[i])
	{
		if (status == 0 && (str[i] == '\'' || str[i] == '\"'))
			status = str[i];
		else if (status == str[i])
			status = 0;
		else
			new[j++] = str[i];
		i++;
	}
	new[j] = '\0';
	return (new);
}

char	*get_env_val(t_env *env, char *key)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (ft_strlen(key) == ft_strlen(temp->key)
			&& ft_strncmp(temp->key, key, ft_strlen(key)) == 0)
			return (ft_strdup(temp->value));
		temp = temp->next;
	}
	return (ft_strdup(""));
}

char	*expand_variable(char *input, int *i, t_mini *mini)
{
	int		start;
	char	*key;
	char	*val;

	start = *i;
	(*i)++;
	if (input[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(mini->exit_code));
	}
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
		(*i)++;
	key = ft_substr(input, start + 1, *i - (start + 1));
	val = get_env_val(mini->env_list, key);
	free(key);
	return (val);
}

void	expand_token(t_mini *mini, t_token *token)
{
	int		i;
	int		in_sq;
	int		in_dq;
	char	*res;
	char	*val;
	char	*temp;

	i = 0;
	in_sq = 0;
	in_dq = 0;
	res = ft_strdup("");
	while (token->value[i])
	{
		if (token->value[i] == '\"' && !in_sq)
			in_dq = !in_dq;
		if (token->value[i] == '\'' && ! in_dq)
			in_sq = !in_sq;
		if (token->value[i] == '$'
			&& !in_sq && is_expansible(&(token->value[i + 1])))
		{
			val = expand_variable(token->value, &i, mini);
			temp = ft_strjoin(res, val);
			free(res);
			free(val);
			res = temp;
		}
		else
		{
			temp = ft_substr(token->value, i, 1);
			val = ft_strjoin(res, temp);
			free(res);
			free(temp);
			res = val;
			i++;
		}
	}
	free(token->value);
	token->value = res;
}
