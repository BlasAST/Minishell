/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:19:40 by andtruji          #+#    #+#             */
/*   Updated: 2025/04/16 12:19:43 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr2(long nn)
{
	int		total;
	char	c;

	total = 0;
	if (nn > 9)
		total += ft_putnbr2(nn / 10);
	c = '0' + (nn % 10);
	total += write (1, &c, 1);
	return (total);
}

int	ft_putnbr(int n, t_opt opt)
{
	long	nn;
	int		total;

	nn = (long)n;
	total = 0;
	if (nn < 0)
	{
		nn = -nn;
		total += write (1, "-", 1);
	}
	else if (opt.plus)
		total += write (1, "+", 1);
	else if (opt.space)
		total += write (1, " ", 1);
	total += ft_putnbr2(nn);
	return (total);
}

int	ft_putstr(char *s)
{
	int	total;

	total = 0;
	if (!s)
		return (write(1, "(null)", 6));
	while (*s)
		total += write (1, s++, 1);
	return (total);
}

int	ft_putchar(char c)
{
	write (1, &c, 1);
	return (1);
}
