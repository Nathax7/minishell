/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 18:11:15 by almeekel          #+#    #+#             */
/*   Updated: 2025/06/25 18:37:23 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*expand_token_value(const char *value, t_quote quote_type,
		char **envp, int exit_status)
{
	if (quote_type == Q_SINGLE)
		return (ft_strdup(value));
	return (expand_variables_in_str(value, quote_type, envp, exit_status));
}

static int	should_field_split(t_quote quote_type)
{
	return (quote_type == Q_NONE || quote_type == Q_MIXED);
}

static int	add_expanded_tokens(char **fields, t_token **head)
{
	int		i;
	char	*field_copy;

	i = 0;
	while (fields && fields[i])
	{
		field_copy = ft_strdup(fields[i]);
		if (!field_copy)
			return (0);
		if (!create_and_append_token(head, field_copy, T_WORD, Q_NONE))
		{
			free(field_copy);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	process_word_expansion(t_token *token, t_token **expanded_head,
		char **envp, int exit_status)
{
	char	*expanded_value;
	char	**fields;

	expanded_value = expand_token_value(token->value, token->quote, envp, exit_status);
	if (!expanded_value)
		return (0);
	if (!should_field_split(token->quote))
	{
		if (!create_and_append_token(expanded_head, expanded_value, T_WORD, Q_NONE))
		{
			free(expanded_value);
			return (0);
		}
		return (1);
	}
	fields = perform_field_splitting(expanded_value, NULL);
	free(expanded_value);
	if (!fields)
		return (0);
	if (!fields[0])
	{
		ft_freesplit(fields);
		return (create_and_append_token(expanded_head, ft_strdup(""), T_WORD, Q_NONE));
	}
	return (add_expanded_tokens(fields, expanded_head));
}

t_token	*expand_tokens(t_token *tokens, char **envp, int exit_status)
{
	t_token	*current;
	t_token	*expanded_head;
	char	*op_copy;

	expanded_head = NULL;
	current = tokens;
	while (current)
	{
		if (current->type == T_WORD)
		{
			if (!process_word_expansion(current, &expanded_head, envp,
					exit_status))
				return (free_token_list_and_return_null(expanded_head));
		}
		else
		{
			op_copy = ft_strdup(current->value);
			if (!op_copy || !create_and_append_token(&expanded_head, op_copy,
					current->type, Q_NONE))
				return (free_token_list_and_return_null(expanded_head));
		}
		current = current->next;
	}
	return (expanded_head);
}
