/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 08:42:46 by andtruji          #+#    #+#             */
/*   Updated: 2025/04/15 08:42:51 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_pointer(void *p)
{
	return (write(1, "0x", 2)
		+ ft_base("0123456789abcdef", (unsigned long) p));
}

int	ft_format(char const **format, va_list args)
{
	t_opt	opt;
	char	type;
	void	*p;

	opt = ft_flags(format);
	type = **format;
	(*format)++;
	if (type == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (type == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (type == 'p')
	{
		p = va_arg(args, void *);
		if (!p)
			return (write(1, "(nil)", 5));
		return (ft_pointer(p));
	}
	else if (type == 'd' || type == 'i')
		return (ft_putnbr(va_arg(args, int), opt));
	else if (type == 'u' || type == 'x' || type == 'X')
		return (ft_bases(&type, args, opt));
	else if (type == '%')
		return (write(1, "%", 1));
	return (0);
}

int	ft_printf(char const *format, ...)
{
	va_list	args;
	int		l;
	int		present;

	l = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%' && (*format + 1))
		{
			format++;
			present = ft_format(&format, args);
			if (present < 0)
				return (-1);
			l += present;
		}
		else
		{
			write (1, format, 1);
			l++;
			format++;
		}
	}
	va_end(args);
	return (l);
}
