/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:27:03 by andtruji          #+#    #+#             */
/*   Updated: 2025/04/16 16:27:07 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_opt	ft_init(void)
{
	t_opt	opt;

	opt.hash = 0;
	opt.plus = 0;
	opt.space = 0;
	return (opt);
}

t_opt	ft_flags(char const **format)
{
	t_opt	opt;

	opt = ft_init();
	while (**format == '#' || **format == '+' || **format == ' ')
	{
		if (**format == '#')
			opt.hash = 1;
		else if (**format == '+')
			opt.plus = 1;
		else if (**format == ' ')
			opt.space = 1;
		(*format)++;
	}
	return (opt);
}

int	ft_base(char *base, unsigned long nb)
{
	size_t	l;
	int		num;

	l = 0;
	num = 0;
	while (base[l])
		l++;
	if (nb >= (unsigned long)l)
		num += ft_base(base, nb / l);
	num += write(1, &base[nb % l], 1);
	return (num);
}

int	ft_bases(const char *format, va_list args, t_opt opt)
{
	unsigned int	nb;

	if (*format == 'u')
		return (ft_base("0123456789", va_arg(args, unsigned int)));
	nb = va_arg(args, unsigned int);
	if (*format == 'x')
	{
		if (opt.hash && nb)
			return (write(1, "0x", 2) + ft_base("0123456789abcdef", nb));
		return (ft_base("0123456789abcdef", nb));
	}
	else if (*format == 'X')
	{
		if (opt.hash && nb)
			return (write(1, "0X", 2) + ft_base("0123456789ABCDEF", nb));
		return (ft_base("0123456789ABCDEF", nb));
	}
	return (0);
}
