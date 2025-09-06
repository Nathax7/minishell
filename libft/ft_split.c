/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:30:41 by nagaudey          #+#    #+#             */
/*   Updated: 2025/08/19 18:06:01 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static size_t	ft_count_words(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

char	**ft_freesplit(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

int	ft_freesplit_int(char **str, int return_val)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (return_val);
}

static size_t	ft_splitlen(char const *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	i;
	size_t	j;
	size_t	k;

	j = 0;
	k = 0;
	tab = (char **)malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!tab)
		return (NULL);
	while (s[k] && j < ft_count_words(s, c))
	{
		i = 0;
		while (s[k] && s[k] == c)
			k++;
		tab[j] = (char *)ft_calloc(sizeof(char), ft_splitlen(s + k, c) + 1);
		if (!tab[j])
			return (ft_freesplit(tab));
		while (s[k] && s[k] != c)
			tab[j][i++] = s[k++];
		j++;
	}
	tab[j] = NULL;
	return (tab);
}
