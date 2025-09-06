/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len_putchar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 20:48:58 by nagaudey          #+#    #+#             */
/*   Updated: 2025/08/19 18:06:31 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../all.h"

int	ft_len_putchar(unsigned char c)
{
	int	error;

	error = write(1, &c, 1);
	return (error);
}
