/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:06:33 by andtruji          #+#    #+#             */
/*   Updated: 2025/04/09 16:06:35 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}*/

#include "libft.h"

char	*ft_strdup(const char *string)
{
	char	*s;
	size_t	i;

	if (!string)
		return (NULL);
	s = malloc((ft_strlen(string) + 1) * sizeof(char));
	if (!s)
		return (NULL);
	i = 0;
	while (string[i] != '\0')
	{
		s[i] = string[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

/*int	main(void)
{
	char *string = "this is a copy";
	char *newstr;
	if ((newstr = ft_strdup(string)) != NULL)
	printf("The new string is: %s\n", newstr);
	return 0;
}*/
