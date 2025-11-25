/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:40:10 by andtruji          #+#    #+#             */
/*   Updated: 2025/04/07 17:40:12 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t count)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!dest && !src)
		return (NULL);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	while (count)
	{
		*d = *s;
		s++;
		d++;
		count--;
	}
	return (dest);
}

/*int	main()
{
	char source[] = "This is the first string";
	char target[] = "This is the second string";
	printf( "Before memcpy, target is \"%s\"\n", target );
	ft_memcpy( target, source, sizeof(source));
	printf( "After memcpy, target becomes \"%s\"\n", target );
	return 0;
}*/
