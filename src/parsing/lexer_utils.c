/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 21:39:08 by almeekel          #+#    #+#             */
/*   Updated: 2025/05/23 18:26:15 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	free_segment_list(t_word_segment *list)
{
	t_word_segment	*current;
	t_word_segment	*next;

	current = list;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}

void	free_token_list(t_token *list)
{
	t_token	*current_token;
	t_token	*next_token;

	current_token = list;
	while (current_token != NULL)
	{
		next_token = current_token->next;
		free(current_token->value);
		free_segment_list(current_token->segments);
		free(current_token);
		current_token = next_token;
	}
}

int	create_and_append_token(t_token **head, char *value, t_token_type type,
		t_quote quote_status, t_word_segment *segments)
{
	t_token	*new_token;
	t_token	*current;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
	{
		free(value);
		free_segment_list(segments);
		return (0);
	}
	new_token->value = value;
	new_token->type = type;
	new_token->quote = quote_status;
	new_token->segments = segments;
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
	return (1);
}

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

int	is_word_char(char c)
{
	if (is_whitespace(c) || c == '|' || c == '<' || c == '>' || c == '\0')
		return (0);
	return (1);
}

int	is_operator_start(char c)
{
	return (c == '|' || c == '<' || c == '>');
}