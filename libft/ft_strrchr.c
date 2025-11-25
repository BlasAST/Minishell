/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:31:10 by andtruji          #+#    #+#             */
/*   Updated: 2025/04/08 15:31:46 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *string, int c)
{
	size_t		i;
	char		*ptr;

	i = 0;
	ptr = NULL;
	while (string[i] != '\0')
	{
		if ((unsigned char)string[i] == (unsigned char)c)
			ptr = (char *)&string[i];
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)&string[i]);
	return (ptr);
}

/*int main(void)
{
  char buffer1[40] = "co.m.puter. prog.ream.....,";
  char * ptr;
  int    ch = '.';
 
  ptr = ft_strrchr( buffer1, ch );
  printf( "The last occurrence of %c in '%s' is '%s'\n",
            ch, buffer1, ptr );
}*/
