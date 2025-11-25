/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:55:30 by andtruji          #+#    #+#             */
/*   Updated: 2025/04/10 14:55:34 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_count_words(const char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			count++;
		i++;
	}
	return (count);
}

void	ft_free_split(char **r, size_t n)
{
	while (n--)
		free(r[n]);
	free(r);
}

char	**ft_split2(char const *s, char c, char **r, size_t i)
{
	size_t	j;
	size_t	p;

	j = 0;
	p = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			j = i;
			while (s[i] != '\0' && s[i] != c)
				i++;
			r[p] = malloc(((i - j) + 1) * sizeof(char));
			if (!r[p])
			{
				ft_free_split(r, p);
				return (NULL);
			}
			ft_strlcpy(r[p++], s + j, ((i - j) + 1));
		}
		else
			i++;
	}
	r[p] = NULL;
	return (r);
}

char	**ft_split(char const *s, char c)
{
	char	**r;
	size_t	i;

	if (!s)
		return (NULL);
	r = malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!r)
		return (0);
	i = 0;
	return (ft_split2(s, c, r, i));
}

/*int	main(void)
{
	char	s[] = ".Good..";
	char	c = '.';
	char	**r = ft_split(s,c);
	
	for (int i = 0; r[i] != NULL; i++)
		printf("[%s]\n", r[i]);
	return (0);
}*/
