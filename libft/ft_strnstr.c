/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:24:16 by nagaudey          #+#    #+#             */
/*   Updated: 2025/08/19 17:28:48 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!little[i])
		return ((char *)big);
	while (big[i] && i < len)
	{
		while (i + j < len && big[i + j] == little[j])
		{
			j++;
			if (little[j] == '\0')
				return ((char *)big + i);
		}
		j = 0;
		i++;
	}
	return (NULL);
}
