/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len_uputnbr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:29:39 by nagaudey          #+#    #+#             */
/*   Updated: 2025/02/06 18:00:25 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../all.h"

size_t	ft_len_uputnbr(unsigned int nb)
{
	size_t			len;
	unsigned int	res;
	unsigned int	temp;

	len = 0;
	res = ft_iterative_count(nb);
	while (res)
	{
		temp = nb / res;
		if (ft_len_putchar((temp % 10) + 48) == -1)
			return (-1);
		res /= 10;
		len++;
	}
	return (len);
}
