/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_processor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:36:09 by almeekel          #+#    #+#             */
/*   Updated: 2025/07/30 18:44:13 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	skip_char_in_qt_content(t_str_builder *sb, const char **line)
{
	if (!sb_append_char(sb, **line))
		return (0);
	(*line)++;
	return (1);
}

int	extract_quoted_content(const char **line, char quote_char,
		t_str_builder *sb)
{
	if (!sb_append_char(sb, quote_char))
		return (0);
	(*line)++;
	while (**line && **line != quote_char)
	{
		if (quote_char == '"' && **line == '\\' && (*(*line + 1) == '$'
				|| *(*line + 1) == '"' || *(*line + 1) == '\\' || *(*line
					+ 1) == '\n'))
		{
			if (skip_char_in_qt_content(sb, line) == 0)
				return (0);
			if (skip_char_in_qt_content(sb, line) == 0)
				return (0);
		}
		else if (skip_char_in_qt_content(sb, line) == 0)
			return (0);
	}
	if (**line == quote_char)
	{
		if (!sb_append_char(sb, quote_char))
			return (0);
		(*line)++;
	}
	return (1);
}

int	extract_unquoted_content(const char **line, t_str_builder *sb)
{
	while (**line && is_word_char(**line) && !is_operator_start(**line)
		&& **line != '\'' && **line != '"')
	{
		if (**line == '\\' && *(*line + 1))
		{
			(*line)++;
			sb_append_char(sb, **line);
		}
		else
		{
			sb_append_char(sb, **line);
		}
		(*line)++;
	}
	return (1);
}

static int	process_quoted_section(const char **line, char quote_char)
{
	(*line)++;
	while (**line && **line != quote_char)
		(*line)++;
	if (**line == quote_char)
	{
		(*line)++;
		return (1);
	}
	return (0);
}

int	has_unclosed_quotes(const char *line)
{
	while (line && *line)
	{
		if (*line == '\'' || *line == '"')
		{
			if (!process_quoted_section(&line, *line))
				return (1);
		}
		else
			line++;
	}
	return (0);
}
