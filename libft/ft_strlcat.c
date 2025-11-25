/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:53:00 by andtruji          #+#    #+#             */
/*   Updated: 2025/04/07 19:53:03 by andtruji         ###   ########.fr       */
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

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	d;
	size_t	s;
	size_t	i;

	d = ft_strlen(dst);
	s = ft_strlen(src);
	if (size <= d)
		return (size + s);
	i = 0;
	while (src[i] != '\0' && i + d < size - 1)
	{
		dst[i + d] = src[i];
		i++;
	}
	dst[i + d] = '\0';
	return (d + s);
}

/*int	main(void)
{
	char d[20] = "si, ";
	char s[] = "hola";
	printf("%zu\n",ft_strlcat(d,s,sizeof(d)));
	printf("%s",d);
	return (0);
}*/
