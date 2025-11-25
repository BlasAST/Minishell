/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:47:20 by andtruji          #+#    #+#             */
/*   Updated: 2025/04/07 16:47:24 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int arg)
{
	if (arg >= 32 && arg <= 126)
		return (1);
	return (0);
}

/*int main(void)
{
	char c = '\n';
	if (ft_isascii(c)) {
	printf("%c exits", c);
	} else {
	printf("%c does not exist", c);
	}
}*/
