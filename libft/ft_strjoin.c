/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:21:27 by nagaudey          #+#    #+#             */
/*   Updated: 2025/06/08 20:36:12 by almeekel         ###   ########.fr       */
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
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	array = (char *)malloc(sizeof(char) * (i + j) + 1);
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
char	*ft_strjoin_space(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*array;

	if (!s1 || !s2)
		return (NULL);
	array = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 2);
	if (!array)
		return (NULL);
	j = 0;
	i = 0;
	while (s1[i])
	{
		array[i] = s1[i];
		i++;
	}
	array[i] = ' ';
	i++;
	while (s2[j])
	{
		array[i + j] = s2[j];
		j++;
	}
	array[i + j] = '\0';
	return (array);
}

char	*ft_strjoin_free(char *s1, char *s2, int free_flag)
{
	char	*result;

	if (!s1 || !s2)
	{
		if (free_flag & 1)
			free(s1);
		if (free_flag & 2)
			free(s2);
		return (NULL);
	}
	result = ft_strjoin(s1, s2);
	if (free_flag & 1)
		free(s1);
	if (free_flag & 2)
		free(s2);
	return (result);
}

// #include <stdio.h>
// int	main(int ac, char **av)
// {
// 	char	*array;

// 	array = ft_strjoin(av[1], av[2]);
// 	printf("%s", array);
// }
