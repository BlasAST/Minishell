/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtruji <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:41:44 by andtruji          #+#    #+#             */
/*   Updated: 2025/04/07 15:41:56 by andtruji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int arg)
{
	if ((arg >= 'a' && arg <= 'z') || (arg >= 'A' && arg <= 'Z'))
		return (1);
	return (0);
}

/*int main(void)
{
	char c = '5';
	if (ft_isalpha(c)) {
	printf("%c is a letter", c);
	} else {
	printf("%c is not a letter", c);
	}
}*/
