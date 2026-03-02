/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blas <blas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 02:45:38 by blas              #+#    #+#             */
/*   Updated: 2026/03/02 03:07:10 by blas             ###   ########.fr       */
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

void	expand_asterisk_token(t_mini mini, t_token *current)
{
	DIR				*dir;
	struct dirent	*d_entry;

	dir = readdir(".");
	if (!dir)
		return ;
	d_entry = readdir(dir);
	while (d_entry != NULL)
	{
		if (d_entry->d_name[0] != '.')
		{
			
		}
		d_entry = readdir(dir);
	}
	closedir(dir);
}

