/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:54:25 by andtruji          #+#    #+#             */
/*   Updated: 2025/04/07 16:54:28 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*s;

	s = str;
	while (n)
	{
		*s = (unsigned char) c;
		s++;
		n--;
	}
	return (str);
}

/*int	main()
{
	char str[] = "hola :)";
	ft_memset(str, 'Z', 4);
	printf("String after memset(): %s\n", str);
	return 0;
}*/
