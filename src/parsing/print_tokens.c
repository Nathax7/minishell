/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 19:21:49 by almeekel          #+#    #+#             */
/*   Updated: 2025/06/25 18:38:02 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static const char	*token_type_to_string(t_token_type type)
{
	switch (type)
	{
	case T_WORD:
		return ("T_WORD");
	case T_PIPE:
		return ("T_PIPE");
	case T_REDIRECT_IN:
		return ("T_REDIRECT_IN");
	case T_REDIRECT_OUT:
		return ("T_REDIRECT_OUT");
	case T_APPEND:
		return ("T_APPEND");
	case T_HEREDOC:
		return ("T_HEREDOC");
	default:
		return ("UNKNOWN");
	}
}

static const char	*quote_type_to_string(t_quote quote)
{
	switch (quote)
	{
	case Q_NONE:
		return ("Q_NONE");
	case Q_SINGLE:
		return ("Q_SINGLE");
	case Q_DOUBLE:
		return ("Q_DOUBLE");
	case Q_MIXED:
		return ("Q_MIXED");
	default:
		return ("UNKNOWN");
	}
}

void	print_token_list(t_token *tokens, const char *stage)
{
	t_token *current;
	int i;

	printf("\n=== TOKENS AT STAGE: %s ===\n", stage);
	if (!tokens)
	{
		printf("No tokens (NULL)\n");
		return ;
	}

	current = tokens;
	i = 0;
	while (current)
	{
		printf("Token %d:\n", i);
		printf("  Type: %s\n", token_type_to_string(current->type));
		printf("  Quote: %s\n", quote_type_to_string(current->quote));
		printf("  Value: \"%s\" (len=%zu)\n",
			current->value ? current->value : "(NULL)",
			current->value ? strlen(current->value) : 0);
		printf("  Raw bytes: ");
		if (current->value)
		{
			for (size_t j = 0; j < strlen(current->value); j++)
				printf("%02x ", (unsigned char)current->value[j]);
		}
		printf("\n\n");
		current = current->next;
		i++;
	}
	printf("=== END TOKENS ===\n\n");
}