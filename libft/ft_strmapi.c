/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 21:37:33 by nagaudey          #+#    #+#             */
/*   Updated: 2025/02/06 17:47:23 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	len;
	char			*array;

	i = 0;
	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	array = (char *)malloc(sizeof(char) * len + 1);
	if (!array)
		return (NULL);
	while (s[i])
	{
		array[i] = (f)(i, s[i]);
		i++;
	}
	array[i] = '\0';
	return (array);
}
