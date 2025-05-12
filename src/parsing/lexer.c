/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 21:40:28 by almeekel          #+#    #+#             */
/*   Updated: 2025/05/12 19:45:59 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

// Extracts the content *within* quotes. Handles basic escapes in double quotes.
// Advances *line_ptr past the closing quote.
// Sets *status: 1 for success, 0 for malloc error, -1 for syntax error (unclosed quote).
static char *extract_quoted_content(const char **line_ptr, char quote_char, int *status)
{
    t_str_builder sb;

    sb_init(&sb);
    (*line_ptr)++; // Skip opening quote
    *status = 1;   // Assume success initially

    while (**line_ptr && **line_ptr != quote_char)
    {
        if (quote_char == '"' && **line_ptr == '\\' && *(*line_ptr + 1) != '\0')
        {
            (*line_ptr)++; // Skip backslash
            // In bash, only $, `, ", \, and newline are special after \ in "..."
            // We handle $, ", \. Other escaped chars are literal (e.g., \t is \t not tab).
            if (**line_ptr == '$' || **line_ptr == '"' || **line_ptr == '\\' || **line_ptr == '`')
            {
                if (!sb_append_char(&sb, **line_ptr)) {*status = 0; break;}
            }
            else // Keep backslash and the char for other escaped characters
            {
                if (!sb_append_char(&sb, '\\')) {*status = 0; break;}
                if (!sb_append_char(&sb, **line_ptr)) {*status = 0; break;}
            }
        }
        else
        {
            if (!sb_append_char(&sb, **line_ptr)) {*status = 0; break;}
        }
        (*line_ptr)++;
    }

    if (*status == 0) // Malloc error during sb_append_char
    {
        sb_free(&sb);
        return (NULL);
    }

    if (**line_ptr == quote_char)
    {
        (*line_ptr)++; // Skip closing quote
        return (sb_to_string(&sb)); // sb_free is done by sb_to_string
    }
    else // Unclosed quote
    {
        report_syntax_error_detail("unclosed quote", (char[]){quote_char, 0});
        sb_free(&sb);
        *status = -1; 
        return (NULL);
    }
}

// Processes a sequence of characters forming a single word, which may consist of
// multiple concatenated segments (quoted or unquoted).
// Creates one T_WORD token with a list of t_word_segment.
static int	process_word_token(const char **line_ptr, t_token **head)
{
    t_str_builder	sb_unquoted;
    t_word_segment	*segments_head = NULL;
    t_word_segment	*new_segment = NULL;
    char			*segment_value = NULL;
    int				status = 1; // 1=ok, 0=malloc error, -1=syntax error

    while (**line_ptr && is_word_char(**line_ptr) && !is_operator_start(**line_ptr))
    {
        if (**line_ptr == '\'' || **line_ptr == '"') // Quoted segment
        {
            char quote_char = **line_ptr;
            segment_value = extract_quoted_content(line_ptr, quote_char, &status);
            if (status <= 0) break; // Malloc or syntax error from extract_quoted_content

            new_segment = create_word_segment(segment_value, (quote_char == '"') ? Q_DOUBLE : Q_SINGLE);
            if (!new_segment) { status = 0; break; } // Malloc error for segment struct itself
            append_segment(&segments_head, new_segment);
        }
        else // Unquoted segment
        {
            sb_init(&sb_unquoted);
            while (**line_ptr && is_word_char(**line_ptr) && !is_operator_start(**line_ptr) &&
                   **line_ptr != '\'' && **line_ptr != '"')
            {
                // Handle backslash escapes in unquoted segments
                if (**line_ptr == '\\' && *(*line_ptr + 1) != '\0')
                {
                    (*line_ptr)++; // Skip backslash, take next char literally
                    if (!sb_append_char(&sb_unquoted, **line_ptr)) { status = 0; break; }
                }
                else
                {
                    if (!sb_append_char(&sb_unquoted, **line_ptr)) { status = 0; break; }
                }
                (*line_ptr)++;
            }
            if (status == 0) { sb_free(&sb_unquoted); break; } // Malloc error in sb_append_char

            segment_value = sb_to_string(&sb_unquoted); // sb_free done by sb_to_string
            if (!segment_value) { status = 0; break; } // Malloc error from sb_to_string

            // Only add non-empty unquoted segments. If sb was empty, segment_value is ""
            if (ft_strlen(segment_value) > 0 || (segments_head != NULL && segments_head->value != NULL) || (*line_ptr && (**line_ptr == '\'' || **line_ptr == '"')))
            { // Add empty unquoted if it's between other segments or followed by quote
                new_segment = create_word_segment(segment_value, Q_NONE);
                if (!new_segment) { free(segment_value); status = 0; break; }
                append_segment(&segments_head, new_segment);
            }
            else
                free(segment_value); // Discard truly empty leading/trailing unquoted segment
        }
        if (status <= 0) break;
    }

    if (status <= 0) // If any error occurred during segment processing
    {
        // Free any segments already added to segments_head for this word
        // Note: create_word_segment frees its input 'value' on its own failure.
        // extract_quoted_content frees its sb on its own failure.
        t_word_segment *current_s = segments_head, *next_s;
        while(current_s) {
            next_s = current_s->next;
            free(current_s->value); // Value was owned by segment
            free(current_s);
            current_s = next_s;
        }
        return (status); // Propagate error status (0 for malloc, -1 for syntax)
    }

    if (segments_head) // If we successfully created at least one segment for this word
    {
        // For T_WORD from lexer: value is NULL, quote is Q_NONE (not relevant here), segments list is attached.
        if (!create_and_append_token(head, NULL, T_WORD, Q_NONE, segments_head))
        {
            // create_and_append_token frees segments on its own failure.
            return (0); // Malloc error
        }
    }
    // If segments_head is NULL (e.g., input was just spaces), no token is created.
    return (1); // Success
}

static int	process_operator_token(const char **line_ptr, t_token **head)
{
    char			*op_val;
    t_token_type	type;

    // ... (existing operator logic remains the same) ...
    if (**line_ptr == '|')
    {
        op_val = ft_strdup("|");
        type = T_PIPE;
        (*line_ptr)++;
    }
    else if (**line_ptr == '<')
    {
        if (*(*line_ptr + 1) == '<')
        {
            op_val = ft_strdup("<<");
            type = T_HEREDOC;
            (*line_ptr) += 2;
        }
        else
        {
            op_val = ft_strdup("<");
            type = T_REDIRECT_IN;
            (*line_ptr)++;
        }
    }
    else if (**line_ptr == '>')
    {
        if (*(*line_ptr + 1) == '>')
        {
            op_val = ft_strdup(">>");
            type = T_APPEND;
            (*line_ptr) += 2;
        }
        else
        {
            op_val = ft_strdup(">");
            type = T_REDIRECT_OUT;
            (*line_ptr)++;
        }
    }
    else
        return (0); // Should not happen
    if (!op_val)
        return (0); // Malloc error
    // For operators: value is op_val, quote is Q_NONE, segments is NULL
    if (!create_and_append_token(head, op_val, type, Q_NONE, NULL))
    {
        // create_and_append_token frees op_val if it fails
        return (0);
    }
    return (1);
}

t_token	*lexer(const char *line)
{
    t_token *head;
    int		status; // 1 for success, 0 for malloc error, -1 for syntax error

    head = NULL;
    status = 1; 
    while (*line && status > 0)
    {
        while (*line && is_whitespace(*line))
            line++;
        if (*line == '\0')
            break ;
        if (is_operator_start(*line))
            status = process_operator_token((const char **)&line, &head);
        else if (is_word_char(*line)) // Any non-operator, non-whitespace start is a word
            status = process_word_token((const char **)&line, &head);
        else // Should not be reached if is_word_char and is_operator_start cover all valid non-whitespace
        {
            report_syntax_error_detail("unexpected character", (char[]){*line, 0});
            status = -1; // Syntax Error
        }
    }

    if (status <= 0) // If lexing failed (malloc or syntax error)
    {
        free_token_list(head); // Clean up any partially created list
        return (NULL);
    }
    return (head);
}