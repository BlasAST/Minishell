/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:05:56 by andtruji          #+#    #+#             */
/*   Updated: 2025/04/08 15:05:58 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *string, int c)
{
	size_t	i;

	i = 0;
	if (!string)
		return (NULL);
	while (string[i] != '\0')
	{
		if ((unsigned char)string[i] == (unsigned char)c)
			return ((char *)&string[i]);
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)&string[i]);
	return (NULL);
}

/*int main(void)
{
  char buffer1[40] = "compu+\0ter program";
  char * ptr;
  int    ch = '\0';
 
  ptr = ft_strchr( buffer1, ch );
  printf( "The first occurrence of %c in '%s' is '%s'\n",
            ch, buffer1, ptr );
}*/
