/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 21:29:46 by nagaudey          #+#    #+#             */
/*   Updated: 2025/08/19 18:04:17 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	*ft_calloc(size_t nmeb, size_t size)
{
	char	*tab;

	if (nmeb == 0 || size == 0)
		return (malloc(0));
	if (nmeb * size > __SIZE_MAX__)
		return (NULL);
	tab = (char *)malloc(nmeb * size);
	if (!tab)
		return (NULL);
	ft_bzero(tab, nmeb * size);
	return (tab);
}
