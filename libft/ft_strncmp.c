/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiguenc <bsiguenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:45:29 by andtruji          #+#    #+#             */
/*   Updated: 2026/02/20 12:40:11 by bsiguenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *string1, const char *string2, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		if (string1[i] != string2[i])
			return ((unsigned char)string1[i] - (unsigned char)string2[i]);
		if (string1[i] == '\0' || string2[i] == '\0')
			break ;
		i++;
	}
	return (0);
}

/*int main() {
  char myStr1[] = "12";
  char myStr2[] = "124";
  int cmp = ft_strncmp(myStr1, myStr2, 6);
  if (cmp > 0) {
    printf("%s is greater than %s\n", myStr1, myStr2);
  } else if (cmp < 0) {
    printf("%s is greater than %s\n", myStr2, myStr1);
  } else {
    printf("%s is equal to %s\n", myStr1, myStr2);
  }
  return 0;
}*/
