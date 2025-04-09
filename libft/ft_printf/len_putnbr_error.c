/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_putnbr_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:21:57 by nagaudey          #+#    #+#             */
/*   Updated: 2025/03/13 00:14:23 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../all.h"

int	len_putnbr_error(int nb)
{
	int				len;
	int				res;
	unsigned int	temp;
	unsigned int	nb2;

	len = 0;
	temp = 0;
	if (nb < 0)
	{
		write(1, "-", 1);
		nb2 = nb * -1;
		len++;
	}
	else
		nb2 = nb;
	res = iterative_count_error(nb2);
	while (res)
	{
		temp = nb2 / res;
		if (len_putchar_error((temp % 10) + 48) == -1)
			return (-1);
		res /= 10;
		len++;
	}
	return (len);
}
