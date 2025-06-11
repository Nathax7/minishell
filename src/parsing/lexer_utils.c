/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 21:39:08 by almeekel          #+#    #+#             */
/*   Updated: 2025/06/04 18:28:23 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	free_token_list(t_token *list)
{
	t_token	*current_token;
	t_token	*next_token;

	current_token = list;
	while (current_token != NULL)
	{
		next_token = current_token->next;
		free(current_token->value);
		free(current_token);
		current_token = next_token;
	}
}

t_token	*free_token_list_and_return_null(t_token *list)
{
	t_token	*current_token;
	t_token	*next_token;

	current_token = list;
	while (current_token != NULL)
	{
		next_token = current_token->next;
		free(current_token->value);
		free(current_token);
		current_token = next_token;
	}
	return (NULL);
}

int	create_and_append_token(t_token **head, char *value, t_token_type type,
		t_quote quote_status)
{
	t_token	*new_token;
	t_token	*current;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
	{
		free(value);
		return (0);
	}
	new_token->value = value;
	new_token->type = type;
	new_token->quote = quote_status;
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

int	is_word_char(char c)
{
	if (ft_isspace(c) || is_operator_start(c) || c == '\0')
		return (0);
	return (1);
}

int	is_operator_start(char c)
{
	return (c == '|' || c == '<' || c == '>');
}
