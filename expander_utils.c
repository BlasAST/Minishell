#include "minishell.h"

char	*remove_quotes(char *str)
{
	char	*new_str;
	int	tq;
	int	i;
	int	j;

	new_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	tq = 1;
	while (str[i])
	{
		if (str[i] == '\'' && tq == 1 && tq != 2)
			tq = 0;
		else if (str[i] == '\"' && tq == 1 || tq != 0)
			tq = 2;
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

char	*expand_variable(char *input, int *i, t_env *env)
{
	int		start;
	char	*key;
	t_env	*tmp;

	if (ft_strncmp(input, "?", 1) == 0)
	{
		if (g_signal_status != 0)
			return (ft_itoa(g_signal_status));
		return (ft_itoa(g_signal_status));
	}
	start = ++(*i);
	while (input[*i] && (ft_isalnum(input[*i] || input[*i] == '_')))
		(*i)++;
	key = ft_strndup(&input[*i], *i - start);
	tmp = env;
	while (tmp && ft_strcmp(tmp->key, key))
		tmp = tmp->next;
	free(key);
	if (tmp)
		return (ft_strdup(tmp->value));
	return (ft_strdup(""));
}

void	expand_token(t_mini *mini, t_token *token)
{
	int	i;
	int	single_quote;
	int	double_quote;
	char *str;

	str = token->value;
	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (str[i] == '\"' && !single_quote)
			double_quote = !double_quote;
		if (str[i] == '$' && !single_quote && (ft_isalpha(str[i+1]) || str[i + 1] == '?'))
		{
			expand_variable(&str[i], &i, mini->env_list);
		}
		else
			i++;
	}
}

