/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 18:20:29 by almeekel          #+#    #+#             */
/*   Updated: 2025/05/28 16:14:29 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static t_quote	determine_quote_type(int has_single, int has_double,
		int has_unquoted)
{
	int	quote_types;

	quote_types = has_single + has_double + has_unquoted;
	if (quote_types > 1)
		return (Q_MIXED);
	if (has_single)
		return (Q_SINGLE);
	if (has_double)
		return (Q_DOUBLE);
	return (Q_NONE);
}

static int	process_word(const char **line, t_token **head)
{
	t_str_builder	sb;
	char			*word_value;
	int				has_single;
	int				has_double;
	int				has_unquoted;

	sb_init(&sb);
	has_single = 0;
	has_double = 0;
	has_unquoted = 0;
	while (**line && is_word_char(**line) && !is_operator_start(**line))
	{
		if (**line == '\'')
		{
			has_single = 1;
			if (!extract_quoted_content(line, '\'', &sb))
				return (sb_free_and_return_zero(&sb));
		}
		else if (**line == '"')
		{
			has_double = 1;
			if (!extract_quoted_content(line, '"', &sb))
				return (sb_free_and_return_zero(&sb));
		}
		else
		{
			has_unquoted = 1;
			if (!extract_unquoted_content(line, &sb))
				return (sb_free_and_return_zero(&sb));
		}
	}
	word_value = sb_to_string_and_free(&sb);
	if (!word_value)
		return (0);
	return (create_and_append_token(head, word_value, T_WORD,
			determine_quote_type(has_single, has_double, has_unquoted)));
}

static int	process_operator(const char **line, t_token **head)
{
	if (**line == '|')
		return (handle_pipe_operator(line, head));
	else if (**line == '<')
		return (handle_lesser_operator(line, head));
	else if (**line == '>')
		return (handle_greater_operator(line, head));
	return (0);
}

int	has_content(const char *line)
{
	while (*line)
	{
		if (!is_whitespace(*line))
			return (1);
		line++;
	}
	return (0);
}

t_token	*lexer(const char *line)
{
	t_token	*head;
	int		status;

	if (!line || !has_content(line))
		return (NULL);
	if (has_unclosed_quotes(line))
		return (NULL);
	head = NULL;
	while (*line)
	{
		while (is_whitespace(*line))
			line++;
		if (!*line)
			break ;
		if (is_operator_start(*line))
			status = process_operator(&line, &head);
		else
			status = process_word(&line, &head);
		if (!status)
		{
			cleanup_and_return_zero(&head);
			return (NULL);
		}
	}
	return (head);
}
