/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_putaddress_error.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 23:51:02 by nagaudey          #+#    #+#             */
/*   Updated: 2025/03/13 00:14:14 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../all.h"

static uintptr_t	iterative_ptr_error(uintptr_t ptr)
{
	uintptr_t	res;

	res = 1;
	while (ptr >= 16)
	{
		ptr /= 16;
		res *= 16;
	}
	return (res);
}

size_t	len_putaddress_error(void *ptr)
{
	size_t		len;
	char		*hex;
	uintptr_t	temp;
	uintptr_t	res;
	uintptr_t	u_ptr;

	hex = "0123456789abcdef";
	u_ptr = (uintptr_t)ptr;
	len = 2;
	if (!u_ptr)
		return (write(2, "(nil)", 5));
	if (write(2, "0x", 2) != 2)
		return (-1);
	res = iterative_ptr_error(u_ptr);
	while (res)
	{
		temp = u_ptr / res;
		if (write(2, (&hex[temp % 16]), 1) == -1)
			return (-1);
		res /= 16;
		len++;
	}
	return (len);
}

/* int	main(void)
{
	char	*ptr;

	printf("%zu\n", ft_len_putaddress((void *)(LONG_MAX)));
	printf("%p\n", LONG_MAX);
} */
