/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespace.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 21:30:20 by nagaudey          #+#    #+#             */
/*   Updated: 2025/04/21 21:33:06 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static int	count_words(const char *str)
{
	int count = 0;
	int in_word = 0;

	while (*str)
	{
		if (isspace(*str))
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		str++;
	}
	return count;
}

static char	*next_word(const char **str)
{
	const char *start;
	int len;

	while (**str && isspace(**str))
		(*str)++;
	start = *str;
	len = 0;
	while (**str && !isspace(**str))
	{
		(*str)++;
		len++;
	}
	return strndup(start, len);
}

char	**ft_split_whitespace(const char *str)
{
	int		word_count;
	char	**result;
	int		i;

	if (!str)
		return NULL;

	word_count = count_words(str);
	result = malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return NULL;

	i = 0;
	while (i < word_count)
	{
		result[i++] = next_word(&str);
	}
	result[i] = NULL;
	return result;
}