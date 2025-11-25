/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:05:38 by andtruji          #+#    #+#             */
/*   Updated: 2025/04/08 16:05:40 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *buf1, const void *buf2, size_t count)
{
	const unsigned char	*b1;
	const unsigned char	*b2;
	size_t				i;

	b1 = buf1;
	b2 = buf2;
	i = 0;
	while (i < count)
	{
		if (b1[i] != b2[i])
			return (b1[i] - b2[i]);
		i++;
	}
	return (0);
}

/*int main() {
  char myStr1[] = "123'\0'56";
  char myStr2[] = "123";
  int cmp = ft_memcmp(myStr1, myStr2, 4);
  if (cmp > 0) {
    printf("%s is greater than %s\n", myStr1, myStr2);
  } else if (cmp < 0) {
    printf("%s is greater than %s\n", myStr2, myStr1);
  } else {
    printf("%s is equal to %s\n", myStr1, myStr2);
  }
  return 0;
}*/
