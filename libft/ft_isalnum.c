/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:47:22 by andtruji          #+#    #+#             */
/*   Updated: 2025/04/07 15:47:25 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int arg)
{
	if (arg >= '0' && arg <= '9')
		return (1);
	if ((arg >= 'a' && arg <= 'z') || (arg >= 'A' && arg <= 'Z'))
		return (1);
	return (0);
}

/*int main(void)
{
	char c = '-';
	if (ft_isalnum(c)) {
	printf("%c is alphanumeric", c);
	} else {
	printf("%c is not alphanumeric", c);
	}
}*/
