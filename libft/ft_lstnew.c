/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:07:16 by andtruji          #+#    #+#             */
/*   Updated: 2025/04/11 11:07:18 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (0);
	node->content = content;
	node->next = NULL;
	return (node);
}

/*int main() {
    char *texto = "Hola mundo!";
    t_list *nodo = ft_lstnew(texto);

    if (nodo) {
        printf("Contenido del nodo: %s\n", (char *)nodo->content);
        free(nodo);  // Liberar la memoria del nodo
    } else {
        printf("Error al crear el nodo\n");
    }

    return 0;
}*/
