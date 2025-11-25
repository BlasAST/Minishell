/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:31:40 by andtruji          #+#    #+#             */
/*   Updated: 2025/04/07 16:31:44 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int arg)
{
	if (arg >= 0 && arg <= 127)
		return (1);
	return (0);
}

/*int main(void)
{
	char c = ' ';
	if (ft_isascii(c)) {
	printf("%c exits", c);
	} else {
	printf("%c does not exist", c);
	}
}*/
