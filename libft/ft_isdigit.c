/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:42:39 by andtruji          #+#    #+#             */
/*   Updated: 2025/04/07 15:42:43 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>

int	ft_isdigit(int arg)
{
	if (arg >= '0' && arg <= '9')
		return (1);
	return (0);
}

/*int main(void)
{
	char c = 'a';
	if (ft_isdigit(c)) {
	printf("%c is a digit", c);
	} else {
	printf("%c is not a digit", c);
	}
}*/
