/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 21:39:08 by almeekel          #+#    #+#             */
/*   Updated: 2025/05/11 21:44:57 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

// Libere la liste de token entiere
void	free_token_list(t_token *list)
{
    t_token	*current;
    t_token	*next;
    t_word_segment *current_segment;
    t_word_segment *next_segment;

    current = list;
    while (current != NULL)
    {
        next = current->next;
        free(current->value); // Value might be NULL if segments are used

        // Free segments if they exist
        current_segment = current->segments;
        while (current_segment != NULL)
        {
            next_segment = current_segment->next;
            free(current_segment->value);
            free(current_segment);
            current_segment = next_segment;
        }
        free(current);
        current = next;
    }
}

// Cree un nouveau token et l'append a la liste
// This function will now be more general.
// For T_WORD from lexer, 'value' will be NULL, 'segments' will be populated.
// For Operators from lexer, 'value' is operator string, 'segments' is NULL, quote_status is Q_NONE.
// For T_WORD from expander, 'value' is final string, 'segments' is NULL, quote_status is Q_NONE.
int	create_and_append_token(t_token **head, char *value, t_token_type type,
	t_quote quote_status, t_word_segment *segments)
{
t_token	*new_token;
t_token	*current;

new_token = (t_token *)malloc(sizeof(t_token));
if (!new_token)
{
	free(value); // Free value if passed and token creation fails
	// Free segments if passed and token creation fails (caller should handle if segments were for this token)
	// For simplicity, assume if segments are passed, value is NULL for raw words.
	if (segments) {
		t_word_segment *seg = segments, *next_seg;
		while(seg) {
			next_seg = seg->next;
			free(seg->value);
			free(seg);
			seg = next_seg;
		}
	}
	return (0);
}
new_token->value = value;
new_token->type = type;
new_token->quote = quote_status;
new_token->segments = segments; // Store segments
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