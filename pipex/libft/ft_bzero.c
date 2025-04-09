/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:42:39 by nagaudey          #+#    #+#             */
/*   Updated: 2025/02/06 17:45:44 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*tab;

	tab = (unsigned char *)s;
	while (n-- > 0)
		*(tab++) = '\0';
}

// #include <stdio.h>
// int main(void)
// {
// 		char	tab[] = "1234";
// 		ft_bzero(tab, 3);
// 		printf("%s", tab);
// }
