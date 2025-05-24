/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 18:20:29 by almeekel          #+#    #+#             */
/*   Updated: 2025/05/23 18:25:00 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static int	append_escaped_char_dq(t_str_builder *sb, const char **line_ptr)
{
	(*line_ptr)++;
	if (**line_ptr == '$' || **line_ptr == '"' || **line_ptr == '\\'
		|| **line_ptr == '`')
	{
		if (!sb_append_char(sb, **line_ptr))
			return (0);
	}
	else
	{
		if (!sb_append_char(sb, '\\'))
			return (0);
		if (!sb_append_char(sb, **line_ptr))
			return (0);
	}
	return (1);
}

static int	append_char_to_quoted_sb(t_str_builder *sb, const char **line_ptr,
		char quote_char)
{
	if (quote_char == '"' && **line_ptr == '\\' && *(*line_ptr + 1) != '\0')
	{
		if (!append_escaped_char_dq(sb, line_ptr))
			return (0);
	}
	else
	{
		if (!sb_append_char(sb, **line_ptr))
			return (0);
	}
	return (1);
}

static char	*extract_quoted_content(const char **line_ptr, char quote_char,
		int *status)
{
	t_str_builder	sb;

	sb_init(&sb);
	(*line_ptr)++;
	*status = 1;
	while (**line_ptr && **line_ptr != quote_char)
	{
		if (!append_char_to_quoted_sb(&sb, line_ptr, quote_char))
		{
			*status = 0;
			break ;
		}
		(*line_ptr)++;
	}
	if (*status == 0)
		return (sb_free(&sb), NULL);
	if (**line_ptr == quote_char)
	{
		(*line_ptr)++;
		return (sb_to_string(&sb));
	}
	report_syntax_error_detail("unclosed quote", (char[]){quote_char, 0});
	*status = -1;
	return (sb_free(&sb), NULL);
}

static int	process_unquoted_segment(const char **line_ptr,
		t_str_builder *sb_unquoted)
{
	sb_init(sb_unquoted);
	while (**line_ptr && is_word_char(**line_ptr)
		&& !is_operator_start(**line_ptr) && **line_ptr != '\''
		&& **line_ptr != '"')
	{
		if (**line_ptr == '\\' && *(*line_ptr + 1) != '\0')
		{
			(*line_ptr)++;
			if (!sb_append_char(sb_unquoted, **line_ptr))
				return (0);
		}
		else
		{
			if (!sb_append_char(sb_unquoted, **line_ptr))
				return (0);
		}
		(*line_ptr)++;
	}
	return (1);
}

static int	add_segment_to_list(t_word_segment **segments_head, char *seg_val,
		t_quote q_type)
{
	t_word_segment	*new_seg;

	new_seg = create_word_segment(seg_val, q_type);
	if (!new_seg)
		return (0);
	append_segment(segments_head, new_seg);
	return (1);
}

static int	process_one_segment(const char **line_ptr,
		t_word_segment **segments_head)
{
	t_str_builder	sb_unq;
	char			*seg_val;
	int				status_extract;

	if (**line_ptr == '\'' || **line_ptr == '"')
	{
		seg_val = extract_quoted_content(line_ptr, **line_ptr, &status_extract);
		if (status_extract <= 0)
			return (status_extract);
		if (!add_segment_to_list(segments_head, seg_val, (*(*line_ptr
						- 1) == '"') ? Q_DOUBLE : Q_SINGLE))
			return (0);
	}
	else
	{
		if (!process_unquoted_segment(line_ptr, &sb_unq))
			return (sb_free(&sb_unq), 0);
		seg_val = sb_to_string(&sb_unq);
		if (!seg_val)
			return (0);
		if (ft_strlen(seg_val) > 0 || (*segments_head != NULL)
			|| (**line_ptr == '\'' || **line_ptr == '"'))
		{
			if (!add_segment_to_list(segments_head, seg_val, Q_NONE))
				return (0);
		}
		else
			free(seg_val);
	}
	return (1);
}

static int	process_word_token(const char **line_ptr, t_token **head)
{
	t_word_segment	*segments_head;
	int				status;

	segments_head = NULL;
	status = 1;
	while (**line_ptr && is_word_char(**line_ptr)
		&& !is_operator_start(**line_ptr) && status > 0)
	{
		status = process_one_segment(line_ptr, &segments_head);
	}
	if (status <= 0)
	{
		free_segment_list(segments_head); // New helper needed
		return (status);
	}
	if (segments_head)
	{
		if (!create_and_append_token(head, NULL, T_WORD, Q_NONE, segments_head))
			return (0);
	}
	return (1);
}

static int	process_operator_token(const char **line_ptr, t_token **head)
{
	char			*op_val;
	t_token_type	type;

	op_val = NULL;
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
		return (0);
	if (!op_val)
		return (0);
	if (!create_and_append_token(head, op_val, type, Q_NONE, NULL))
		return (0);
	return (1);
}

t_token	*lexer(const char *line)
{
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
			status = process_operator_token(&line, &head);
		else if (is_word_char(*line))
			status = process_word_token(&line, &head);
		else
		{
			report_syntax_error_detail("unexpected character", (char[]){*line,
				0});
			status = -1;
		}
	}
	if (status <= 0)
		return (free_token_list(head), NULL);
	return (head);
}
