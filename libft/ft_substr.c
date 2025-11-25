/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:30:26 by andtruji          #+#    #+#             */
/*   Updated: 2025/04/08 19:30:33 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	lens;
	char	*c;
	size_t	i;

	lens = ft_strlen(s);
	if (start >= lens)
		len = 0;
	else if (start + len > lens)
		len = lens - start;
	if (!s)
		return (0);
	c = malloc((len + 1));
	if (!c)
		return (0);
	i = 0;
	while (i < len && s[start + i] != '\0')
	{
		c[i] = s[start + i];
		i++;
	}
	c[i] = '\0';
	return (c);
}

/*int main(void)
{
	char *str = "Hello, world!";
	char *substr = ft_substr(str, 7, 6);
	if (substr)
	{
		printf("Subcadena:%s\n", substr);
		free(substr);
	}
	return 0;
}*/
