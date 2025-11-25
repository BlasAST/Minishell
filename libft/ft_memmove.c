/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:06:32 by andtruji          #+#    #+#             */
/*   Updated: 2025/04/07 18:06:37 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t count)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = dest;
	s = src;
	if (d < s)
	{
		while (count--)
			*d++ = *s++;
	}
	else if (d > s)
	{
		d += count;
		s += count;
		while (count--)
			*--d = *--s;
	}
	return (dest);
}

/*int	main(void)
{
	char target[21] = "a shiny white sphere";
	char * p = target + 8;
	char * source = target + 2;
	printf( "Before memmove, target is \"%s\"\n", target );
	ft_memmove( p, source, 5 );
	printf( "After memmove, target becomes \"%s\"\n", target );
	char original2[] = "123456789";

	ft_memmove(original2, original2 + 2, 5);
	printf("result: %s\n", original2);
}*/
