/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:30:41 by nagaudey          #+#    #+#             */
/*   Updated: 2025/04/14 17:34:30 by nagaudey         ###   ########.fr       */
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

static size_t	ft_splitlen(char const *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

char	**ft_split(t_node *alloc, char const *s, char c)
{
	char	**tab;
	size_t	i;
	size_t	j;
	size_t	k;

	j = 0;
	k = 0;
	tab = ft_malloc(sizeof(char *) * (ft_count_words(s, c) + 1), alloc);
	while (s[k] && j < ft_count_words(s, c))
	{
		i = 0;
		while (s[k] && s[k] == c)
			k++;
		tab[j] = (char *)ft_calloc(alloc, sizeof(char), ft_splitlen(s + k, c) + 1);
		while (s[k] && s[k] != c)
			tab[j][i++] = s[k++];
		j++;
	}
	tab[j] = NULL;
	return (tab);
}

// #include <stdio.h>

// int	main(int ac, char **av)
// {
// 	char	**array;
// 	ac = 1;
// 	array = ft_split(av[1], *av[2]);
// 	int i = 0;
// 	while (4)
//     {
//         printf("%s\n",array[i]);
// 		if (!array[i])
// 			break ;
//         i++;
// 	}
// }
