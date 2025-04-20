/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 12:42:41 by Mimoulapino       #+#    #+#             */
/*   Updated: 2025/04/20 17:00:37 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

// Supprime les quotes comme bash le fait
// - simples quotes : litteralement
// - double quotes : $ sera expand plus tard

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}
char	*remove_quotes(const char *src)
{
	char	*dst;
	int		i;
	int		j;
	char	quote;

	dst = malloc(ft_strlen(src) + 1);
	if (!dst)
		return (NULL);
	i = 0;
	j = 0;
	quote = 0;
	while (src[i])
	{
		if (!quote && is_quote(src[i]))
		{
			quote = src[i];
			i++;
			continue ;
		}
		else if (quote && src[i] == quote)
		{
			quote = 0;
			i++;
			continue ;
		}
		dst[j++] = src[i++];
	}
	dst[j] = '\0';
	return (dst);
}

// Fonction à appeler après la tokenization pour nettoyer les quotes
void	process_quotes(t_token *tokens)
{
	char *cleaned;

	while (tokens)
	{
		if (tokens->type == T_WORD)
		{
			cleaned = remove_quotes(tokens->value);
			free(tokens->value);
			tokens->value = cleaned;
		}
		tokens = tokens->next;
	}
}