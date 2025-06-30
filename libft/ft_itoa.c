/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:30:50 by nagaudey          #+#    #+#             */
/*   Updated: 2025/02/06 17:47:23 by nagaudey         ###   ########.fr       */
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
// #include <stdio.h>

// int	main(void)
// {
// 	int	n;

// 	n = -1165165572;
// 	ft_itoa(n);
// 	printf("%d", n);
// }
