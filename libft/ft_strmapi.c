/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 08:38:17 by andtruji          #+#    #+#             */
/*   Updated: 2025/04/11 08:38:20 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdlib.h>
#include <stdio.h>

size_t	ft_strlen(const char *s)
{
	size_t	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	my_mapper(unsigned int i, char c)
{
	if (i % 2 == 0)
		return (c - 32);
	return (c);
}*/
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*r;
	size_t	l;
	size_t	i;

	if (!s || !f)
		return (NULL);
	l = ft_strlen(s);
	r = malloc((l + 1) * sizeof(char));
	if (!r)
		return (0);
	r[l] = '\0';
	i = 0;
	while (i < l)
	{
		r[i] = f(i, s[i]);
		i++;
	}
	return (r);
}

/*int	main(void)
{
	char *s = "hello!";
	char *r = ft_strmapi(s, my_mapper);
	printf("%s\n", r); // Output: "HeLlO!"
	free(r);
	return 0;
}*/
