/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterative_count_error.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:50:27 by nagaudey          #+#    #+#             */
/*   Updated: 2025/03/13 00:14:08 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../all.h"

int	iterative_count_error(unsigned int nbr)
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
