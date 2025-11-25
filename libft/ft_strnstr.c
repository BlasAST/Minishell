/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:37:39 by andtruji          #+#    #+#             */
/*   Updated: 2025/04/08 16:37:41 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*little == '\0')
		return ((char *)big);
	while (i < len && *big)
	{
		j = 0;
		while (little[j] && little[j] == big[i + j] && (i + j) < len)
			j++;
		if (little[j] == '\0')
			return ((char *)big + i);
		i++;
	}
	return (0);
}

/*int main(void)
{
	const char *str = "Holmun a mundo cruel";
	const char *find = "mundo";
	char *res = ft_strnstr(str, find, 15);

	if (res)
		printf("Encontrado: %s\n", res);
	else
		printf("No se encontró\n");

	return 0;
}*/
