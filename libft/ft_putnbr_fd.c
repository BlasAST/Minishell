/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:34:32 by andtruji          #+#    #+#             */
/*   Updated: 2025/04/11 10:34:34 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nn;
	char	c;

	nn = (long)n;
	if (nn < 0)
	{
		nn = -nn;
		write (fd, "-", 1);
	}
	if (nn == 0)
	{
		write (fd, "0", 1);
		return ;
	}
	if (nn > 9)
		ft_putnbr_fd(nn / 10, fd);
	c = '0' + (nn % 10);
	write (fd, &c, 1);
}

/*int	main(void)
{
	int	num = 2;
	ft_putnbr_fd(num, 1);
	return 0;
}*/
