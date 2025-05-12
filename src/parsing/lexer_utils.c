/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 21:39:08 by almeekel          #+#    #+#             */
/*   Updated: 2025/05/12 19:44:21 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

// Libere la liste de token entiere
void	free_token_list(t_token *list)
{
    t_token	*current_token;
    t_token	*next_token;
    t_word_segment *current_segment;
    t_word_segment *next_segment;

    current_token = list;
    while (current_token != NULL)
    {
        next_token = current_token->next;
        free(current_token->value); // Value might be NULL if segments are used by this token

        // Free segments if they exist for this token
        current_segment = current_token->segments;
        while (current_segment != NULL)
        {
            next_segment = current_segment->next;
            free(current_segment->value);
            free(current_segment);
            current_segment = next_segment;
        }
        free(current_token);
        current_token = next_token;
    }
}

// Helper to create a word segment
t_word_segment	*create_word_segment(char *value, t_quote quote_type)
{
    t_word_segment *new_segment;

    new_segment = (t_word_segment *)malloc(sizeof(t_word_segment));
    if (!new_segment)
    {
        free(value); // Free the passed value if segment creation fails
        return (NULL);
    }
    new_segment->value = value; // Takes ownership of value
    new_segment->quote_type = quote_type;
    new_segment->next = NULL;
    return (new_segment);
}

// Helper to append a segment to a list of segments
void append_segment(t_word_segment **head, t_word_segment *new_segment)
{
    t_word_segment *current;

    if (!new_segment)
        return;
    if (*head == NULL)
    {
        *head = new_segment;
    }
    else
    {
        current = *head;
        while (current->next)
            current = current->next;
        current->next = new_segment;
    }
}

// Cree un nouveau token et l'append a la liste
// For T_WORD from lexer: 'value' is NULL, 'segments' is populated.
// For Operators from lexer: 'value' is operator string, 'segments' is NULL, quote_status is Q_NONE.
// For T_WORD from expander: 'value' is final string, 'segments' is NULL, quote_status is Q_NONE.
int	create_and_append_token(t_token **head, char *value, t_token_type type,
        t_quote quote_status, t_word_segment *segments)
{
    t_token	*new_token;
    t_token	*current;

    new_token = (t_token *)malloc(sizeof(t_token));
    if (!new_token)
    {
        free(value); // Free value if passed and token creation fails
        if (segments) // If segments were meant for this token, free them
        {
            t_word_segment *seg = segments, *next_seg;
            while(seg) {
                next_seg = seg->next;
                free(seg->value);
                free(seg);
                seg = next_seg;
            }
        }
        return (0); // Malloc error
    }
    new_token->value = value;         // Takes ownership of value if not NULL
    new_token->type = type;
    new_token->quote = quote_status;
    new_token->segments = segments;   // Takes ownership of segments list if not NULL
    new_token->next = NULL;
    if (*head == NULL)
        *head = new_token;
    else
    {
        current = *head;
        while (current->next != NULL)
            current = current->next;
        current->next = new_token;
    }
    return (1); // Success
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