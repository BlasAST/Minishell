/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blas <blas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 14:02:19 by blas              #+#    #+#             */
/*   Updated: 2026/03/06 01:18:42 by blas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	match_pattern(char *pattern, char *str)
{
	if (*pattern == '\0')
		return (*str == '\0');
	if (*pattern == '*')
	{
		while (*pattern == '*')
			pattern++;
		if (*pattern == '\0')
			return (1);
		while (*str)
		{
			if (match_pattern(pattern, str))
				return (1);
			str++;
		}
		return (0);
	}
	if (*pattern == *str)
		return (match_pattern(pattern + 1, str + 1));
	return (0);
}

int	count_matches(char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	int				count;

	count = 0;
	dir = opendir(".");
	if (!dir)
		return (0);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (!(entry->d_name[0] == '.' && pattern[0] != '.'))
		{
			if (match_pattern(pattern, entry->d_name))
				count++;
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (count);
}

static void	sort_matches(char **arr, int count)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(arr[j], arr[j + 1]) > 0)
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

char	**get_wildcard_matches(char *pattern, int count)
{
	char			**arr;
	DIR				*dir;
	struct dirent	*entry;
	int				i;

	arr = malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	dir = opendir(".");
	i = 0;
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (!(entry->d_name[0] == '.' && pattern[0] != '.'))
		{
			if (match_pattern(pattern, entry->d_name))
				arr[i++] = ft_strdup(entry->d_name);
		}
		entry = readdir(dir);
	}
	arr[i] = NULL;
	closedir(dir);
	sort_matches(arr, count);
	return (arr);
}
