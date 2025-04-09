/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_uputnbr_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:29:39 by nagaudey          #+#    #+#             */
/*   Updated: 2025/03/13 00:15:34 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../all.h"

size_t	len_uputnbr_error(unsigned int nb)
{
	size_t			len;
	unsigned int	res;
	unsigned int	temp;

	len = 0;
	res = iterative_count_error(nb);
	while (res)
	{
		temp = nb / res;
		if (len_putchar_error((temp % 10) + 48) == -1)
			return (-1);
		res /= 10;
		len++;
	}
	return (len);
}
