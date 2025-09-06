/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 20:38:24 by nagaudey          #+#    #+#             */
/*   Updated: 2025/08/19 17:29:11 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../all.h"

static size_t	argformat_error(char format, va_list args)
{
	size_t	printed;

	printed = 0;
	if (format == 'c')
		printed += len_putchar_error(va_arg(args, int));
	if (format == 's')
		printed += len_putstr_error(va_arg(args, const char *));
	if (format == 'p')
		printed += len_putaddress_error(va_arg(args, void *));
	if (format == 'd' || format == 'i')
		printed += len_putnbr_error(va_arg(args, int));
	if (format == 'u')
		printed += len_uputnbr_error(va_arg(args, unsigned int));
	if (format == 'x' || format == 'X')
		printed += len_putnbr_hex_error(va_arg(args, unsigned int),
				format == 'X');
	if (format == '%')
		printed += len_putchar_error('%');
	return (printed);
}

int	ft_printf_error(int exit, const char *format, ...)
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
			printed += argformat_error(format[i], args);
		else
			printed += len_putchar_error(format[i]);
		i++;
	}
	va_end(args);
	exit_error(exit);
	return (-1);
}
