/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_extracter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:36:09 by almeekel          #+#    #+#             */
/*   Updated: 2025/05/27 20:04:15 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	extract_quoted_content(const char **line, char quote, t_str_builder *sb)
{
	(*line)++;
	while (**line && **line != quote)
	{
		sb_append_char(sb, **line);
		(*line)++;
	}
	if (**line != quote)
		return (0);
	(*line)++;
	return (1);
}

int	extract_unquoted_content(const char **line, t_str_builder *sb)
{
	while (**line && is_word_char(**line) && !is_operator_start(**line)
		&& **line != '\'' && **line != '"')
	{
		sb_append_char(sb, **line);
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
	while (*line)
	{
		if (*line == '\'' || *line == '"')
		{
			if (!process_quoted_section(&line, *line))
				return (1);
		}
		else
		{
			line++;
		}
	}
	return (0);
}

int	handle_quote_continuation(char **line)
{
	char	*new_line;
	char	*updated_line;

	new_line = secure_readline(get_continuation_prompt(PROMPT_QUOTE));
	if (!new_line)
		return (0);
	updated_line = accumulate_input(*line, new_line);
	free(new_line);
	if (!updated_line)
		return (0);
	*line = updated_line;
	return (1);
}
