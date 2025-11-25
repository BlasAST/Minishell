/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:35:25 by andtruji          #+#    #+#             */
/*   Updated: 2025/04/11 12:35:27 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}

/*int main(void)
{
	t_list *head = NULL;
	t_list *new_node;
	new_node = ft_lstnew((void *)42);
	ft_lstadd_front(&head, new_node);
	
	new_node = ft_lstnew((void *)36);
	ft_lstadd_front(&head, new_node);
	
	t_list *temp = head;
	while (temp)
	{
		printf("%d\n", (int)temp->content);
		temp = temp->next;
	}
	while (head)
	{
		t_list *temp = head;
		head = head->next;
		free(temp);
	}
	return 0;
}*/
