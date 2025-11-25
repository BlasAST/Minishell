/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:20:34 by andtruji          #+#    #+#             */
/*   Updated: 2025/04/11 10:20:37 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		write (fd, s, 1);
		s++;
	}
	write (fd, "\n", 1);
}

/*int	main(void)
{
	// Caso 1: Cadena válida
	char *str1 = "Hola Mundo!";
	ft_putendl_fd(str1, 1);  // Salida esperada: "Hola Mundo!\n"

	// Caso 2: Cadena vacía
	char *str2 = " .";
	ft_putendl_fd(str2, 1);  // Salida esperada: "\n" (solo el salto de línea)

	// Caso 3: Cadena NULL
	char *str3 = NULL;
	ft_putendl_fd(str3, 1);  // No debe imprimir nada

	return 0;
}*/
