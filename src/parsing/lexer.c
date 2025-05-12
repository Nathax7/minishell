/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 21:40:28 by almeekel          #+#    #+#             */
/*   Updated: 2025/05/11 22:33:59 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

// process_quoted_segment now builds a value for a single quoted segment
// It returns the *content* of the quotes.
// The caller (process_word_token) will create a t_word_segment with this.
static char *extract_quoted_content(const char **line_ptr, char quote_char, int *status)
{
    t_str_builder sb;

    sb_init(&sb);
    (*line_ptr)++; // Skip opening quote

    while (**line_ptr && **line_ptr != quote_char)
    {
        // Handle escapes within double quotes
        if (quote_char == '"' && **line_ptr == '\\' && *(*line_ptr + 1) != '\0')
        {
            (*line_ptr)++; // Skip backslash
            // In bash, only $, `, ", \, and newline are special after \ in "..."
            // For simplicity, let's say we escape $, ", \. Others are literal.
            if (**line_ptr == '$' || **line_ptr == '"' || **line_ptr == '\\')
            {
                if (!sb_append_char(&sb, **line_ptr)) { *status = 0; break; }
            }
            else // Keep backslash and the char
            {
                if (!sb_append_char(&sb, '\\')) { *status = 0; break; }
                if (!sb_append_char(&sb, **line_ptr)) { *status = 0; break; }
            }
        }
        else
        {
            if (!sb_append_char(&sb, **line_ptr)) { *status = 0; break; }
        }
        (*line_ptr)++;
    }

    if (*status == 0) // Malloc error in sb_append_char
    {
        sb_free(&sb);
        return (NULL);
    }

    if (**line_ptr == quote_char)
    {
        (*line_ptr)++; // Skip closing quote
        *status = 1;
        return (sb_to_string(&sb)); // sb_free is done by sb_to_string if successful
    }
    else // Unclosed quote
    {
        report_syntax_error_detail("unclosed quote", (char[]){quote_char, 0});
        sb_free(&sb);
        *status = -1; // Syntax error
        return (NULL);
    }
}

static int	process_word_token(const char **line_ptr, t_token **head)
{
    t_str_builder	sb_unquoted;
    t_word_segment	*segments_head = NULL;
    t_word_segment	*new_segment_node = NULL;
    char			*segment_value;
    int				status = 1; // 1 = ok, 0 = malloc error, -1 = syntax error

    while (**line_ptr && is_word_char(**line_ptr) && !is_operator_start(**line_ptr) && status > 0)
    {
        if (**line_ptr == '\'' || **line_ptr == '"')
        {
            char quote_char = **line_ptr;
            segment_value = extract_quoted_content(line_ptr, quote_char, &status);
            if (status <= 0) break; // Error or malloc failure

            new_segment_node = create_word_segment(segment_value, (quote_char == '"') ? Q_DOUBLE : Q_SINGLE);
            if (!new_segment_node) { status = 0; break; } // Malloc failure for segment struct
            append_segment(&segments_head, new_segment_node);
        }
        else // Unquoted segment part
        {
            sb_init(&sb_unquoted);
            while (**line_ptr && is_word_char(**line_ptr) && !is_operator_start(**line_ptr) &&
                   **line_ptr != '\'' && **line_ptr != '"')
            {
                if (**line_ptr == '\\' && *(*line_ptr + 1) != '\0') // Handle backslash escape
                {
                    (*line_ptr)++;
                    // In unquoted context, backslash preserves literal value of next char,
                    // unless it's a newline (line continuation, not handled here for simplicity).
                    if (!sb_append_char(&sb_unquoted, **line_ptr)) { status = 0; break; }
                }
                else
                {
                    if (!sb_append_char(&sb_unquoted, **line_ptr)) { status = 0; break; }
                }
                (*line_ptr)++;
            }
            if (status == 0) { sb_free(&sb_unquoted); break; }
            
            segment_value = sb_to_string(&sb_unquoted); // sb_free is done by sb_to_string
            if (!segment_value) { status = 0; break; }

            if (ft_strlen(segment_value) > 0) // Only add if non-empty
            {
                new_segment_node = create_word_segment(segment_value, Q_NONE);
                if (!new_segment_node) { free(segment_value); status = 0; break; }
                append_segment(&segments_head, new_segment_node);
            }
            else
            {
                free(segment_value); // Empty unquoted segment, discard
            }
        }
    }

    if (status <= 0) // Error occurred
    {
        // Free already created segments for this word
        t_word_segment *seg = segments_head, *next_seg;
        while(seg) { next_seg = seg->next; free(seg->value); free(seg); seg = next_seg; }
        return (status); // 0 for malloc error, -1 for syntax
    }

    if (segments_head) // If any segments were created for this word
    {
        // For T_WORD from lexer: value is NULL, quote is Q_NONE (irrelevant), segments list is attached.
        if (!create_and_append_token(head, NULL, T_WORD, Q_NONE, segments_head))
        {
            // create_and_append_token failure should free segments if it fails internally
            return (0); // Malloc error
        }
    }
    // If segments_head is NULL (e.g. input was just "" or '' that resulted in no actual content segments)
    // then no token is created for this "empty" word. Bash often behaves this way.
    // Or, if "" or '' should be an empty token, logic to create an empty segment might be needed.
    // Current logic: if `extract_quoted_content` returns empty string for "" or '', a segment with "" is created.
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
// ... (lexer main loop remains structurally similar, calling the modified process_word_token and process_operator_token) ...
    t_token *head;
    int status;

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
        else if (is_word_char(*line))
            status = process_word_token((const char **)&line, &head);
        else 
        {
            report_syntax_error_detail("unexpected character", (char[]){*line, 0});
            status = -1; // Syntax Error
        }
    }
    if (status <= 0) 
    {
        free_token_list(head);
        return (NULL);
    }
    return (head);
}