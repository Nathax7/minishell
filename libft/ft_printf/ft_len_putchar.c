/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len_putchar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 20:48:58 by nagaudey          #+#    #+#             */
/*   Updated: 2025/02/06 18:00:15 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../all.h"

int	ft_len_putchar(unsigned char c)
{
	int	error;

	error = write(1, &c, 1);
	return (error);
}

// #include <stdio.h>

// int main(void)
// {
// 	printf("%s", "12345");
// }
