/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:04:33 by nagaudey          #+#    #+#             */
/*   Updated: 2025/05/27 22:08:25 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*dup;

	i = 0;
	while (s && s[i])
		i++;
	dup = (char *)malloc(sizeof(char) * i + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (s && s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
// #include <stdio.h>
// int	main(int ac, char **av)
// {
// 	char	*tab;

// 	tab = ft_strdup("123");
// 	printf("%s", tab);
// }
