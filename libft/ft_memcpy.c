/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:36:13 by nagaudey          #+#    #+#             */
/*   Updated: 2025/08/19 18:05:55 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dest2;
	const char		*src2;

	i = 0;
	dest2 = dest;
	src2 = src;
	while (i < n)
	{
		dest2[i] = src2[i];
		i++;
	}
	return (dest);
}
