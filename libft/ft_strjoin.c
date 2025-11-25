/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:37:03 by andtruji          #+#    #+#             */
/*   Updated: 2025/04/09 14:37:07 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*c;
	size_t	i;
	size_t	j;

	if (!s2 || !s1)
		return (NULL);
	c = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!c)
		return (0);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
		c[j++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		c[j++] = s2[i++];
	c[j] = '\0';
	return (c);
}

/*int	main(void)
{
	char	s1[]= "There are ";
	char	s2[]= "a lot of people.";
	printf("%s", ft_strjoin(s1, s2));
	return (0);
}*/
