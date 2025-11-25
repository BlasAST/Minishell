/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:21:18 by andtruji          #+#    #+#             */
/*   Updated: 2025/04/07 17:21:21 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *str, size_t n)
{
	unsigned char	*s;

	s = str;
	while (n)
	{
		*s = '\0';
		s++;
		n--;
	}
}

/*int	main()
{
	char str[] = "hola :)";
	ft_bzero(str, 4);
	printf("String after bzero(): %s\n", str);
	return 0;
}*/
