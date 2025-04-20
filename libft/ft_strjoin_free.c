/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:02:18 by almeekel          #+#    #+#             */
/*   Updated: 2025/04/20 17:04:20 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

char	*ft_strjoin_free(char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*new;

	if (!s2)
		return (s1);
	len1 = s1 ? ft_strlen(s1) : 0;
	len2 = ft_strlen(s2);
	new = malloc(len1 + len2 + 1);
	if (!new)
	{
		free(s1);
		return (NULL);
	}
	if (s1)
	{
		ft_memcpy(new, s1, len1);
		free(s1);
	}
	ft_memcpy(new + len1, s2, len2);
	new[len1 + len2] = '\0';
	return (new);
}

char	*ft_strjoin_free_c(char *s1, char c)
{
	size_t	len;
	char	*new;

	len = s1 ? ft_strlen(s1) : 0;
	new = malloc(len + 2);
	if (!new)
	{
		free(s1);
		return (NULL);
	}
	if (s1)
	{
		ft_memcpy(new, s1, len);
		free(s1);
	}
	new[len] = c;
	new[len + 1] = '\0';
	return (new);
}
