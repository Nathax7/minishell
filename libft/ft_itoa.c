/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:30:50 by nagaudey          #+#    #+#             */
/*   Updated: 2025/08/19 17:28:40 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static int	ft_size(int n)
{
	int	size;

	size = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		size++;
		n = -n;
	}
	while (n)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	int		size;
	char	*array;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	size = ft_size(n);
	array = (char *)malloc(sizeof(char) * (size + 1));
	if (!array)
		return (NULL);
	array[size] = '\0';
	if (n == 0)
		array[0] = '0';
	if (n < 0)
	{
		array[0] = '-';
		n = -n;
	}
	while (n)
	{
		array[--size] = (n % 10) + '0';
		n /= 10;
	}
	return (array);
}
