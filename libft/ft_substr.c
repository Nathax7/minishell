/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:59:05 by nagaudey          #+#    #+#             */
/*   Updated: 2025/02/06 17:47:23 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	size;
	char	*array;

	size = 0;
	i = 0;
	if (start >= ft_strlen(s))
	{
		array = (char *)malloc(1);
		if (!array)
			return (NULL);
		array[0] = '\0';
		return (array);
	}
	while (size < len && s[start + size])
		size++;
	array = (char *)malloc(sizeof(char) * (size + 1));
	if (!array)
		return (NULL);
	while (s[start] && i < size)
		array[i++] = s[start++];
	array[i] = '\0';
	return (array);
}
// #include <stdio.h>
// int	main(int ac, char **av)
// {
// 	char	*array;

// 	array = ft_substr(av[1], 2, 5);
// 	printf("%s", array);
// }
