#include "minishell.h"

char	*remove_quotes(char *str)
{
	char	*new_str;
	char	quote;
	int		i;
	int		j;

	new_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	quote = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && quote == 0)
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		else
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

char	*get_env_val(t_env *env, char *key)
{
	t_env	*env_temp;

	env_temp = env;
	while (env_temp)
	{
		if (strncmp(env_temp->key, key, ft_strlen(key) + 1) == 0)
			return (ft_strdup(env_temp->value));
		env_temp = env_temp->next;
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
		if (token->value[i] == '$' && !in_sq && (ft_isalnum(token->value[i + 1])
				|| token->value[i + 1] == '_' || token->value [i + 1] == '?'))
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

