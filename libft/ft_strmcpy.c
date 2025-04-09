/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 00:51:05 by nagaudey          #+#    #+#             */
/*   Updated: 2025/02/23 20:19:08 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	ft_strmcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		i++;
	}
	dest = malloc(sizeof(char) * i + 1);
	if (!dest)
		return ;
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}
