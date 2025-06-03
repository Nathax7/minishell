/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:21:27 by nagaudey          #+#    #+#             */
/*   Updated: 2025/05/24 14:59:35 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*array;

	if (!s1 || !s2)
		return (NULL);
	array = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!array)
		return (NULL);
	j = 0;
	i = 0;
	while (s1[i])
	{
		array[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		array[i + j] = s2[j];
		j++;
	}
	array[i + j] = '\0';
	return (array);
}
// #include <stdio.h>
// int	main(int ac, char **av)
// {
// 	char	*array;

// 	array = ft_strjoin(av[1], av[2]);
// 	printf("%s", array);
// }
