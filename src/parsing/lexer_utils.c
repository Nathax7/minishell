/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 21:39:08 by almeekel          #+#    #+#             */
/*   Updated: 2025/05/10 22:37:28 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

// Libere la liste de token entiere
void	free_token_list(t_token *list)
{
	t_token	*current;
	t_token	*next;

	current = list;
	while (current != NULL)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}

// Cree un nouveau token et l'append a la liste
int	create_and_append_token(t_token **head, char *value, t_token_type type,
		t_quote quote_status)
{
	t_token	*new_token;
	t_token	*current;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
	{
		free(value); // Free la valeur dupliquee si la creation de token echoue
		return (0);
	}
	new_token->value = value; // value est deja dup
	new_token->type = type;
	new_token->quote = quote_status;
	new_token->next = NULL;
	if (*head == NULL)
	{
		*head = new_token;
	}
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_token;
	}
	return (1);
}

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

// Verifie si un character peut faire partie d'un mot sans quote ou a besoin de gestion speciale
int	is_word_char(char c)
{
	if (is_whitespace(c) || c == '|' || c == '<' || c == '>' || c == '\0')
		return (0);
	return (1);
}

// Verifie si operateur
int	is_operator_start(char c)
{
	return (c == '|' || c == '<' || c == '>');
}