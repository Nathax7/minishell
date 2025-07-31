/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_tokenizer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:27:45 by almeekel          #+#    #+#             */
/*   Updated: 2025/07/30 18:35:25 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_quote	determine_quote_type(int has_single, int has_double,
		int has_unquoted)
{
	int	quote_types;

	quote_types = has_single + has_double + has_unquoted;
	if (has_single)
		return (Q_SINGLE);
	if (has_double)
		return (Q_DOUBLE);
	return (Q_NONE);
}

static int	process_quote_content(const char **line, t_str_builder *sb,
		t_quote_flags *flags)
{
	if (**line == '\'')
	{
		flags->has_single = 1;
		if (!extract_quoted_content(line, '\'', sb))
			return (0);
	}
	else if (**line == '"')
	{
		flags->has_double = 1;
		if (!extract_quoted_content(line, '"', sb))
			return (0);
	}
	return (1);
}

static int	extract_word_content(const char **line, t_str_builder *sb,
		t_quote_flags *flags)
{
	while (**line && !ft_isspace(**line) && !is_operator_start(**line))
	{
		if (**line == '\'' || **line == '"')
		{
			if (!process_quote_content(line, sb, flags))
				return (0);
		}
		else
		{
			flags->has_unquoted = 1;
			if (!extract_unquoted_content(line, sb))
				return (0);
		}
	}
	return (1);
}

int	process_word(const char **line, t_token **head)
{
	t_str_builder	sb;
	char			*word_value;
	t_quote_flags	flags;

	sb_init(&sb);
	flags.has_single = 0;
	flags.has_double = 0;
	flags.has_unquoted = 0;
	if (!extract_word_content(line, &sb, &flags))
		return (sb_free_and_return_zero(&sb));
	word_value = sb_to_string_and_free(&sb);
	if (!word_value)
		return (0);
	return (create_and_append_token(head, word_value, T_WORD,
			determine_quote_type(flags.has_single, flags.has_double,
				flags.has_unquoted)));
}
