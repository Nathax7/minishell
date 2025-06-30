/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:35:36 by nagaudey          #+#    #+#             */
/*   Updated: 2025/02/06 17:47:23 by nagaudey         ###   ########.fr       */
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
// #include <stdio.h>
// #include <string.h>
// int	main(int argc, char **argv)
// {
// 	size_t	n;
// 	char	tab[6] = "1234";
// 	char	tab2[6] = "1234";

// 	ft_memmove(tab + 1, tab, 5);
// 	memmove(tab2 + 1, tab2, 5);
// 	printf("%s\n", tab);
// 	printf("%s", tab2);
// }
