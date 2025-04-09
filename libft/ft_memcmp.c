/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:37:46 by nagaudey          #+#    #+#             */
/*   Updated: 2025/02/06 17:47:23 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	unsigned const char	*s3;
	unsigned const char	*s4;

	i = 0;
	s3 = s1;
	s4 = s2;
	if (n == 0)
		return (0);
	while (i + 1 < n && s3[i] == s4[i])
		i++;
	return (s3[i] - s4[i]);
}
