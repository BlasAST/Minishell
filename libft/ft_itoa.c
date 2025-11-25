/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 07:27:03 by andtruji          #+#    #+#             */
/*   Updated: 2025/04/11 07:27:05 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_cantidad(int n)
{
	int	c;

	c = 0;
	if (n <= 0)
		c = 1;
	while (n != 0)
	{
		n /= 10;
		c++;
	}
	return (c);
}

char	*ft_itoa(int n)
{
	int		l;
	char	*s;
	long	nn;

	l = ft_cantidad(n);
	s = malloc((l + 1) * sizeof(char));
	if (!s)
		return (0);
	s[l] = '\0';
	nn = n;
	if (nn < 0)
	{
		s[0] = '-';
		nn = -nn;
	}
	if (nn == 0)
		s[0] = '0';
	while (nn > 0)
	{
		s[--l] = '0' + nn % 10;
		nn /= 10;
	}
	return (s);
}

/*int	main(void)
{
	int	n = -159;
	printf("%s", ft_itoa(n));
	return (0);
}*/
