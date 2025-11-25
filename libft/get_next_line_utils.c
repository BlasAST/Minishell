/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:44:26 by andtruji          #+#    #+#             */
/*   Updated: 2025/04/25 15:44:27 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_node(t_list_fd **lst, t_list_fd *node)
{
	t_list_fd	*temp;

	if (!lst || !*lst || !node)
		return ;
	if (*lst == node)
	{
		*lst = node->next;
		free(node->store);
		free(node);
		return ;
	}
	temp = *lst;
	while (temp && temp->next != node)
		temp = temp->next;
	if (temp->next == node)
	{
		temp->next = node->next;
		free(node->store);
		free(node);
		return ;
	}
}

char	*ft_join_free(char *s1, char const *s2)
{
	char	*c;
	size_t	i;
	size_t	j;

	if (!s2 && !s1)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	c = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!c)
		return (free(s1), NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
		c[j++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		c[j++] = s2[i++];
	c[j] = '\0';
	free(s1);
	return (c);
}
