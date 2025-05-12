/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:07:26 by almeekel          #+#    #+#             */
/*   Updated: 2025/05/11 21:46:48 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

// Main pour faire les expansions sur la liste token, 
// retourne une liste de token sans free la liste originale
// ELLE NEXPAND QUE LA VAR POUR LINSTANT AJOUTER LA TILDE GLOBBING ETC !!!!
// IL MANQUE AUSSI LE SPLIT DES MOTS APRES UNE EXPANSION SANS QUOTE !
t_token	*perform_all_expansions(t_token *raw_list_head, char **envp,
		int current_exit_status)
{
	t_token *current_raw_token;
	t_token *expanded_list_head = NULL;
	t_str_builder final_word_sb; // Used to concatenate segment results for a single word

	current_raw_token = raw_list_head;
	while (current_raw_token)
	{
		if (current_raw_token->type == T_WORD)
		{
			sb_init(&final_word_sb);
			t_word_segment *current_segment = current_raw_token->segments;
			while (current_segment)
			{
				char *segment_content_to_expand = current_segment->value;
				char *expanded_segment_value = NULL;

				if (current_segment->quote_type != Q_SINGLE)
				{
					expanded_segment_value = expand_variables_in_str(
						segment_content_to_expand,
						current_segment->quote_type, // Pass segment's quote type
						envp,
						current_exit_status);
				}
				else
				{
					// Single-quoted segments are not expanded for variables
					expanded_segment_value = ft_strdup(segment_content_to_expand);
				}

				if (!expanded_segment_value)
				{
					sb_free(&final_word_sb);
					free_token_list(expanded_list_head);
					// report_error("expander", "memory allocation failure in segment expansion", 0);
					// g_exit_status = 1;
					return (NULL);
				}
				
				// Quote removal for the segment's original quotes is implicitly handled
				// because the lexer stored the *content* of quotes in segment->value.
				// The segment->quote_type was used to control expansion.

				if (!sb_append_str(&final_word_sb, expanded_segment_value))
				{
					free(expanded_segment_value);
					sb_free(&final_word_sb);
					free_token_list(expanded_list_head);
					// report_error("expander", "memory allocation failure appending segment", 0);
					// g_exit_status = 1;
					return (NULL);
				}
				free(expanded_segment_value);
				current_segment = current_segment->next;
			}

			char *final_word_value = sb_to_string(&final_word_sb); // sb_free is done by sb_to_string
			if (!final_word_value)
			{
				free_token_list(expanded_list_head);
				// report_error("expander", "memory allocation failure for final word", 0);
				// g_exit_status = 1;
				return (NULL);
			}

			// Create a new token for the expanded list.
			// Value is the concatenated string, quote is Q_NONE, segments is NULL.
			if (!create_and_append_token(&expanded_list_head, final_word_value, T_WORD, Q_NONE, NULL))
			{
				// create_and_append_token frees final_word_value on failure
				free_token_list(expanded_list_head);
				// report_error("expander", "token creation failure for expanded word", 0);
				// g_exit_status = 1;
				return (NULL);
			}
		}
		else // Operator tokens are passed through (copied)
		{
			char *op_value_copy = ft_strdup(current_raw_token->value);
			if (!op_value_copy)
			{
				free_token_list(expanded_list_head);
				return (NULL); // Malloc error
			}
			if (!create_and_append_token(&expanded_list_head, op_value_copy,
										current_raw_token->type, Q_NONE, NULL))
			{
				// create_and_append_token frees op_value_copy on failure
				free_token_list(expanded_list_head);
				return (NULL); // Malloc error
			}
		}
		current_raw_token = current_raw_token->next;
	}
	return (expanded_list_head);
}