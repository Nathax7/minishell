/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 21:29:46 by nagaudey          #+#    #+#             */
/*   Updated: 2025/04/10 16:22:02 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	*ft_calloc(size_t nmeb, size_t size)
{
	char	*tab;

	if (nmeb == 0 || size == 0)
		return (ft_malloc(0, g_signal.node));
	if (nmeb * size > __SIZE_MAX__)
		return (NULL);
	tab = ft_malloc(nmeb * size, g_signal.node);
	ft_bzero(tab, nmeb * size);
	return (tab);
}
// #include <stdio.h>

// int	main(void)
// {
// 	char	*tab;

// 	tab = ft_calloc(4, sizeof(char));
// 	tab = "123";
// 	printf("%s", tab);
// }
