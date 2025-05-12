/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:07:26 by almeekel          #+#    #+#             */
/*   Updated: 2025/05/12 19:46:44 by almeekel         ###   ########.fr       */
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
	t_token			*current_raw_token;
	t_token			*expanded_list_head = NULL;
	t_str_builder	final_word_sb; // Used to concatenate segment results for a single word

	current_raw_token = raw_list_head;
	while (current_raw_token)
	{
		if (current_raw_token->type == T_WORD)
		{
			sb_init(&final_word_sb);
			t_word_segment *current_segment = current_raw_token->segments;
			if (!current_segment && current_raw_token->value) // Should not happen if lexer populates segments
			{
				// This case is a fallback or indicates an already processed token.
				// For safety, if a T_WORD has a value but no segments, treat its value as a single segment.
				// This part might need adjustment based on how T_WORD tokens are handled if they bypass segmentation.
				char *expanded_val = expand_variables_in_str(current_raw_token->value, current_raw_token->quote, envp, current_exit_status);
				if (expanded_val) {
					sb_append_str(&final_word_sb, expanded_val);
					free(expanded_val);
				} else { /* Malloc error */ sb_free(&final_word_sb); free_token_list(expanded_list_head); return NULL; }
			}
			
			while (current_segment)
			{
				char *segment_content_to_expand = current_segment->value;
				char *expanded_segment_value = NULL;

				// Perform variable expansion only if not single-quoted
				if (current_segment->quote_type != Q_SINGLE)
				{
					expanded_segment_value = expand_variables_in_str(
						segment_content_to_expand,
						current_segment->quote_type, // Pass segment's original quote type for context
						envp,
						current_exit_status);
				}
				else
				{
					// For single-quoted segments, the value is literal, no variable expansion.
					expanded_segment_value = ft_strdup(segment_content_to_expand);
				}

				if (!expanded_segment_value) // Malloc error from expansion or strdup
				{
					sb_free(&final_word_sb);
					free_token_list(expanded_list_head);
					// report_error("expander", "memory allocation failure in segment processing", 0);
					// g_exit_status = 1; // Assuming g_exit_status is accessible
					return (NULL);
				}
				
				// The expanded_segment_value is now the processed content of that segment.
				// Quotes that controlled expansion (like $ in "$VAR") are gone.
				// Literal quotes from single-quoted segments are still in expanded_segment_value.
				// This is where "quote removal" for literal quotes would happen if desired *before* concatenation.
				// However, standard behavior is to concatenate, and then the final string is treated as one argument.

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
			// Value is the concatenated string from all segments.
			// Original segments are not carried over; quote status is now Q_NONE.
			// TODO: Implement field splitting here if final_word_value needs to be split into multiple tokens.
			// For now, one T_WORD token from lexer results in one T_WORD token after expansion.
			if (!create_and_append_token(&expanded_list_head, final_word_value, T_WORD, Q_NONE, NULL))
			{
				// create_and_append_token frees final_word_value on its own failure.
				free_token_list(expanded_list_head);
				// report_error("expander", "token creation failure for expanded word", 0);
				// g_exit_status = 1;
				return (NULL);
			}
		}
		else // Operator tokens are passed through (copied)
		{
			// Operators don't have segments and are not expanded.
			char *op_value_copy = ft_strdup(current_raw_token->value);
			if (!op_value_copy)
			{
				free_token_list(expanded_list_head);
				return (NULL); // Malloc error
			}
			// Operator tokens have NULL segments and Q_NONE quote status.
			if (!create_and_append_token(&expanded_list_head, op_value_copy,
										current_raw_token->type, Q_NONE, NULL))
			{
				// create_and_append_token frees op_value_copy on its own failure.
				free_token_list(expanded_list_head);
				return (NULL); // Malloc error
			}
		}
		current_raw_token = current_raw_token->next;
	}
	return (expanded_list_head);
}