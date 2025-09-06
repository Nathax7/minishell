/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:50:43 by nagaudey          #+#    #+#             */
/*   Updated: 2025/08/19 17:28:55 by almeekel         ###   ########.fr       */
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
