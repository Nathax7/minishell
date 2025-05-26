/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_putstr_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 20:50:08 by nagaudey          #+#    #+#             */
/*   Updated: 2025/03/31 17:35:33 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../all.h"

size_t	len_putstr_error(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (write(2, "(null)", 6));
	if (write(2, &str[i], ft_strlen(str)) == -1)
		return (-1);
	return (i);
}
