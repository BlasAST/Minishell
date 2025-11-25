/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:06:43 by andtruji          #+#    #+#             */
/*   Updated: 2025/04/09 15:06:47 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}*/
#include "libft.h"

int	ft_inset(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	l;
	char	*c;

	if (!s1 || !set)
		return (0);
	i = 0;
	while (s1[i] && ft_inset(s1[i], set))
		i++;
	j = ft_strlen(s1);
	while (j > i && ft_inset(s1[j - 1], set))
		j--;
	l = j - i;
	c = malloc((l + 1) * sizeof(char));
	if (!c)
		return (0);
	l = 0;
	while (i < j)
		c[l++] = s1[i++];
	c[l] = '\0';
	return (c);
}

/*int main()
{
    char *s1 = "   ***Hello, World!**  *   ";
    char *set = " *";
    char *result = ft_strtrim(s1, set);
    if (result)
    {
        printf("Trimmed string: '%s'\n", result);
        free(result);
    }
    else
    {
        printf("Memory allocation failed.\n");
    }
    return 0;
}*/
