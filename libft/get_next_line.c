/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:44:06 by andtruji          #+#    #+#             */
/*   Updated: 2025/04/25 15:44:07 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_free_line(char *store)
{
	char	*new_storee;
	char	*new_store;

	new_storee = ft_strchr(store, '\n');
	if (!new_storee)
		return (free(store), NULL);
	new_store = ft_strdup(new_storee + 1);
	free(store);
	return (new_store);
}

char	*ft_line(char *store)
{
	int		i;
	char	*line;
	int		j;

	i = 0;
	if (!store || store[i] == '\0')
		return (NULL);
	while (store[i] != '\n' && store[i])
		i++;
	if (store[i] == '\n')
		i++;
	line = malloc((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	j = 0;
	i = 0;
	while (store[i] != '\n' && store[i])
		line[j++] = store[i++];
	if (store[i] == '\n')
		line[j++] = '\n';
	line[j] = '\0';
	return (line);
}

t_list_fd	*ft_add_find_fd(t_list_fd **lst, int fd)
{
	t_list_fd	*temp;

	temp = *lst;
	while (temp)
	{
		if (temp->fd == fd)
			return (temp);
		temp = temp->next;
	}
	temp = malloc(sizeof(t_list_fd));
	if (!temp)
		return (NULL);
	temp->fd = fd;
	temp->next = *lst;
	temp->store = NULL;
	*lst = temp;
	return (temp);
}

char	*get_next_line2(t_list_fd **lst, t_list_fd *node)
{
	char		*buffer;
	int			readd;
	char		*line;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	readd = 1;
	while ((!node->store || !ft_strchr(node->store, '\n')) && readd > 0)
	{
		readd = read(node->fd, buffer, BUFFER_SIZE);
		if (readd == -1)
			return (free(buffer), ft_free_node(lst, node), NULL);
		buffer[readd] = '\0';
		node->store = ft_join_free(node->store, buffer);
	}
	line = ft_line(node->store);
	node->store = ft_free_line(node->store);
	if (!node->store || node->store[0] == '\0')
		ft_free_node(lst, node);
	return (free(buffer), line);
}

char	*get_next_line(int fd)
{
	static t_list_fd	*lst;
	t_list_fd			*node;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	node = ft_add_find_fd(&lst, fd);
	if (!node)
		return (NULL);
	return (get_next_line2(&lst, node));
}
