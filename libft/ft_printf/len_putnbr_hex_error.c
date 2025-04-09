/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_putnbr_hex_error.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:03:31 by nagaudey          #+#    #+#             */
/*   Updated: 2025/03/13 00:14:59 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../all.h"

static int	iterative_hex_error(unsigned int nbr)
{
	int	res;

	res = 1;
	while (nbr >= 16)
	{
		nbr /= 16;
		res *= 16;
	}
	return (res);
}

size_t	len_putnbr_hex_error(unsigned int nbr, int flag)
{
	size_t			len;
	char			*hex;
	unsigned int	temp;
	unsigned int	res;

	len = 0;
	if (flag)
		hex = "0123456789ABCDEF";
	else
		hex = "0123456789abcdef";
	res = iterative_hex_error(nbr);
	while (res)
	{
		temp = nbr / res;
		if (len_putchar_error(hex[temp % 16]) == -1)
			return (-1);
		res /= 16;
		len++;
	}
	return (len);
}

// int	main(void)
// {
// 	printf("\n%zu", ft_len_putnbr_hex(1234, 0));
// }
