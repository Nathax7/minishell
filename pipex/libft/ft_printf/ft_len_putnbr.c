/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len_putnbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:21:57 by nagaudey          #+#    #+#             */
/*   Updated: 2025/02/06 18:00:18 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../all.h"

int	ft_len_putnbr(int nb)
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
	res = ft_iterative_count(nb2);
	while (res)
	{
		temp = nb2 / res;
		if (ft_len_putchar((temp % 10) + 48) == -1)
			return (-1);
		res /= 10;
		len++;
	}
	return (len);
}
