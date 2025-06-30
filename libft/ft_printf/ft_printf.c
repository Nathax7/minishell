/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 20:38:24 by nagaudey          #+#    #+#             */
/*   Updated: 2025/02/07 17:40:03 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../all.h"

static size_t	ft_argformat(char format, va_list args)
{
	size_t	printed;

	printed = 0;
	if (format == 'c')
		printed += ft_len_putchar(va_arg(args, int));
	if (format == 's')
		printed += ft_len_putstr(va_arg(args, const char *));
	if (format == 'p')
		printed += ft_len_putaddress(va_arg(args, void *));
	if (format == 'd' || format == 'i')
		printed += ft_len_putnbr(va_arg(args, int));
	if (format == 'u')
		printed += ft_len_uputnbr(va_arg(args, unsigned int));
	if (format == 'x' || format == 'X')
		printed += ft_len_putnbr_hex(va_arg(args, unsigned int), format == 'X');
	if (format == '%')
		printed += ft_len_putchar('%');
	return (printed);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	size_t	printed;
	size_t	i;

	va_start(args, format);
	printed = 0;
	i = 0;
	if (!format)
		return (-1);
	while (format[i])
	{
		if (format[i] == '%' && (format[++i] == 'c' || format[i] == 's'
				|| format[i] == 'p' || format[i] == 'd' || format[i] == 'i'
				|| format[i] == 'u' || format[i] == 'x' || format[i] == 'X'
				|| format[i] == '%'))
			printed += ft_argformat(format[i], args);
		else
			printed += ft_len_putchar(format[i]);
		i++;
	}
	va_end(args);
	return (printed);
}
// #include <stdio.h>

// int main(void)
// {
// 	printf(" Size : %d\n", printf("%d", 42));
// 	printf(" Size : %d\n", ft_printf("%ld", 42));
// }
