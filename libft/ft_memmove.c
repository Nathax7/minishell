/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:35:36 by nagaudey          #+#    #+#             */
/*   Updated: 2025/08/19 17:28:59 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dest2;
	unsigned const char	*src2;
	size_t				i;

	dest2 = dest;
	src2 = src;
	i = 0;
	if (src2 < dest2)
	{
		while (i < n)
		{
			dest2[n - i - 1] = src2[n - i - 1];
			i++;
		}
	}
	else
		while (n-- > 0)
			*(dest2++) = *(src2++);
	return (dest);
}
