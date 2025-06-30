/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:34:26 by nagaudey          #+#    #+#             */
/*   Updated: 2025/02/06 17:44:57 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int	ft_atoi(const char *str)
{
	long int	result;
	int			sign;
	size_t		i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -sign;
	while (str[i] <= '9' && str[i] >= '0')
	{
		if ((result * 10 + str[i] - '0') / 10 != result)
		{
			if (sign == -1)
				return ((int)LONG_MIN);
			return ((int)LONG_MAX);
		}
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * sign);
}

// #include <stdio.h>
// int	main(int ac, char **av)
// {
// 	int	x;

// 	x = ft_atoi("-12315425424545");
// 	printf("%d\n", x);
// 	x = atoi("-12354564646545645");
// 	printf("%d", x);
// }
//   if (res > (INT_MAX - (str[i] - '0')) / 10)
//         return ((x == 1) ? INT_MAX : INT_MIN);
