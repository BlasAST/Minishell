/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:31:05 by andtruji          #+#    #+#             */
/*   Updated: 2025/04/09 15:31:08 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	char	*s;
	size_t	i;

	s = malloc(size * num);
	if (!s)
		return (NULL);
	i = 0;
	while (i < size * num)
		s[i++] = 0;
	return ((void *)s);
}
