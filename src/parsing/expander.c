/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 18:11:15 by almeekel          #+#    #+#             */
/*   Updated: 2025/05/23 18:13:50 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static int	should_field_split(t_word_segment *segments)
{
	t_word_segment	*current;

	current = segments;
	while (current)
	{
		if (current->quote_type == Q_SINGLE || current->quote_type == Q_DOUBLE)
			return (0);
        if (current->quote_type == Q_NONE)
            return (2);
		current = current->next;
	}
	return (1);
}

static int	create_tokens_from_fields(char **fields,
		t_token **expanded_list_head)
{
	int		i;
	char	*field_copy;

	i = 0;
	if (!fields)
		return (1);
	while (fields[i])
	{
		field_copy = ft_strdup(fields[i]);
		if (!field_copy)
			return (0);
		if (!create_and_append_token(expanded_list_head, field_copy, T_WORD,
				Q_NONE, NULL))
			return (0);
		i++;
	}
	return (1);
}

// --- New Helper Functions for Decomposition ---

static char	*expand_one_segment(t_word_segment *segment, char **envp,
		int exit_status)
{
	if (segment->quote_type != Q_SINGLE)
		return (expand_variables_in_str(segment->value, segment->quote_type,
				envp, exit_status));
	else
		return (ft_strdup(segment->value));
}

// Processes all segments of a T_WORD token, returning the concatenated result.
// Returns NULL on malloc error.
static char	*process_and_concatenate_segments(t_word_segment *segments,
		char **envp, int exit_status, t_str_builder *sb)
{
	t_word_segment	*current_seg;
	char			*expanded_val;

	current_seg = segments;
	sb_init(sb);
	while (current_seg)
	{
		expanded_val = expand_one_segment(current_seg, envp, exit_status);
		if (!expanded_val)
			return (sb_free(sb), NULL);
		if (!sb_append_str(sb, expanded_val))
		{
			free(expanded_val);
			return (sb_free(sb), NULL);
		}
		free(expanded_val);
		current_seg = current_seg->next;
	}
	return (sb_to_string(sb)); // sb_free is done by sb_to_string
}

// Handles a T_WORD token: expands, optionally field splits, adds to list.
// Returns 0 on error (expanded_list_head will be freed by caller).
static int	process_expanded_word_token(t_token *raw_token,
		t_token **expanded_list_head, char **envp, int exit_status)
{
	t_str_builder	final_word_sb;
	char			*final_value;
	char			**fields;
	int				split_this;

	final_value = process_and_concatenate_segments(raw_token->segments, envp,
			exit_status, &final_word_sb);
	if (!final_value)
		return (0);
	split_this = should_field_split(raw_token->segments);
	if (split_this && final_value[0] != '\0')
	{
		fields = perform_field_splitting(final_value, NULL);
		free(final_value);
		if (!fields)
			return (0);
		if (!create_tokens_from_fields(fields, expanded_list_head))
			return (free_char_array(fields), 0);
		free_char_array(fields);
	}
	else
	{
		if (!create_and_append_token(expanded_list_head, final_value, T_WORD,
				Q_NONE, NULL))
			return (0); // create_and_append_token frees final_value on failure
	}
	return (1);
}

// Handles an operator token (non-T_WORD).
// Returns 0 on error (expanded_list_head will be freed by caller).
static int	process_operator_token_expansion(t_token *raw_token,
		t_token **expanded_list_head)
{
	char	*value_copy;

	value_copy = ft_strdup(raw_token->value);
	if (!value_copy)
		return (0);
	if (!create_and_append_token(expanded_list_head, value_copy,
			raw_token->type, Q_NONE, NULL))
	{
		// create_and_append_token frees value_copy on its failure
		return (0);
	}
	return (1);
}

// --- Main Expansion Function ---

t_token	*perform_all_expansions(t_token *raw_list_head, char **envp,
		int current_exit_status)
{
	t_token *current_raw;
	t_token *expanded_list_head;
	int success;

	expanded_list_head = NULL;
	current_raw = raw_list_head;
	success = 1;
	while (current_raw)
	{
		if (current_raw->type == T_WORD)
			success = process_expanded_word_token(current_raw,
					&expanded_list_head, envp, current_exit_status);
		else
			success = process_operator_token_expansion(current_raw,
					&expanded_list_head);
		if (!success)
		{
			free_token_list(expanded_list_head);
			return (NULL);
		}
		current_raw = current_raw->next;
	}
	return (expanded_list_head);
}