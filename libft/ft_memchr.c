/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:25:06 by andtruji          #+#    #+#             */
/*   Updated: 2025/04/09 18:25:08 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*str;

	i = 0;
	str = s;
	while (i < n)
	{
		if (str[i] == (unsigned char) c)
			return ((void *)&str[i]);
		i++;
	}
	return (NULL);
}

/*int	main(void)
{
	char myStr[] = "Hello World!";
	char *myPtr = (char*)ft_memchr(myStr, 'o', 12);
	if (myPtr != NULL) {
	printf("%s", myPtr);
  }
  return 0;
}*/
