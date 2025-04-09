/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:50:43 by nagaudey          #+#    #+#             */
/*   Updated: 2025/02/11 16:04:00 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*array;

	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_strchr((char *)set, s1[start]))
		start++;
	end--;
	while (ft_strchr((char *)set, s1[end]))
		end--;
	array = ft_substr(s1, start, (end - start + 1));
	return (array);
}
// #include <stdio.h>
// int main(int ac, char **av)
// {
// 	printf("%s\n", ft_strtrim(av[1], av[2]));
// 	//printf("%p\n", ft_strchr((char *)"1", "11123456111"[10]));
// }
