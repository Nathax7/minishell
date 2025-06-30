/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:24:37 by almeekel          #+#    #+#             */
/*   Updated: 2025/06/27 16:42:38 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	*ft_strcat(char *dest, const char *src)
{
	char *dest_ptr;
	int i;

	if (!dest || !src)
		return (dest);
	dest_ptr = dest;
	while (*dest_ptr)
		dest_ptr++;
	i = 0;
	while (src[i])
	{
		*dest_ptr = src[i];
		dest_ptr++;
		i++;
	}
	*dest_ptr = '\0';
	return (dest);
}