/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_putchar_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 20:48:58 by nagaudey          #+#    #+#             */
/*   Updated: 2025/08/19 18:06:19 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../all.h"

int	len_putchar_error(unsigned char c)
{
	int	error;

	error = write(2, &c, 1);
	return (error);
}
