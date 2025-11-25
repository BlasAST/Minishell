/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 16:57:14 by andtruji          #+#    #+#             */
/*   Updated: 2025/09/29 16:57:20 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

static int	is_valid_base(char *base)
{
	int	i;
	int	j;

	i = 0;
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-' || is_space(base[i]))
			return (0);
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	return (i >= 2);
}

static int	get_index(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_atoi_base(char *str, char *base)
{
	int	sign;
	int	result;
	int	base_len;
	int	idx;

	if (!is_valid_base(base))
		return (0);
	base_len = ft_strlen(base);
	sign = 1;
	result = 0;
	while (is_space(*str))
		str++;
	while (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = -sign;
	idx = get_index(*str, base);
	while (idx != -1)
	{
		result = result * base_len + idx;
		str++;
		idx = get_index(*str, base);
	}
	return (result * sign);
}
