/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 20:38:24 by nagaudey          #+#    #+#             */
/*   Updated: 2025/08/19 17:29:10 by almeekel         ###   ########.fr       */
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
