/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:38:42 by nagaudey          #+#    #+#             */
/*   Updated: 2025/02/06 17:47:23 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

unsigned int	ft_strlcat(char *dest, char *src, size_t size)
{
	unsigned int	i;
	unsigned int	len_dest;
	unsigned int	len_src;

	i = 0;
	len_dest = 0;
	len_src = 0;
	while (dest[len_dest] && len_dest < size)
		len_dest++;
	while (src[len_src])
		len_src++;
	if (size == 0)
		return (len_src);
	while (src[i] && len_dest + i < size - 1)
	{
		dest[len_dest + i] = src[i];
		i++;
	}
	if (len_dest < size)
		dest[len_dest + i] = '\0';
	return (len_dest + len_src);
}
