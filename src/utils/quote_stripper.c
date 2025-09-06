/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_stripper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mimoulapinou <bebefripouille@chaton.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 13:49:12 by almeekel          #+#    #+#             */
/*   Updated: 2025/08/16 19:31:12 by Mimoulapino      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

static void	process_quote_removal(const char *str, char *result, size_t len,
		int in_quotes)
{
	size_t	i;
	size_t	j;
	char	quote_char;

	i = 0;
	j = 0;
	quote_char = 0;
	while (i < len)
	{
		if (!in_quotes && (str[i] == '\'' || str[i] == '"'))
		{
			quote_char = str[i];
			in_quotes = 1;
			i++;
		}
		else if (in_quotes && str[i] == quote_char)
		{
			in_quotes = 0;
			quote_char = 0;
			i++;
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
}

char	*remove_outer_quotes(const char *str)
{
	size_t	len;
	char	*result;
	int		in_quotes;

	in_quotes = 0;
	if (!str || !*str)
		return (ft_strdup(""));
	len = ft_strlen(str);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	process_quote_removal(str, result, len, in_quotes);
	return (result);
}
