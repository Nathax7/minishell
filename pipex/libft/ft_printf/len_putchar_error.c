/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_putchar_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 20:48:58 by nagaudey          #+#    #+#             */
/*   Updated: 2025/03/13 00:14:18 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../all.h"

int	len_putchar_error(unsigned char c)
{
	int	error;

	error = write(2, &c, 1);
	return (error);
}

// #include <stdio.h>

// int main(void)
// {
// 	printf("%s", "12345");
// }
