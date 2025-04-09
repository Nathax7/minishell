/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_count.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:50:27 by nagaudey          #+#    #+#             */
/*   Updated: 2025/02/06 18:00:13 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../all.h"

int	ft_iterative_count(unsigned int nbr)
{
	int	res;

	res = 1;
	while (nbr >= 10)
	{
		nbr /= 10;
		res *= 10;
	}
	return (res);
}
