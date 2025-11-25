/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:47:29 by andtruji          #+#    #+#             */
/*   Updated: 2025/04/11 12:47:31 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

/*int main(void)
{
	t_list *head = NULL;
	t_list *new_node;
	new_node = ft_lstnew((void *)42);
	ft_lstadd_front(&head, new_node);
	new_node = ft_lstnew((void *)36);
	ft_lstadd_front(&head, new_node);

	int size = ft_lstsize(head);
	printf("El tamaño de la lista es: %d\n", size);
	while (head)
	{
		t_list *temp = head;
		head = head->next;
		free(temp);
	}
	return 0;
}*/
