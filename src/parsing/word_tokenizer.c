/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_tokenizer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mimoulapinou <bebefripouille@chaton.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:27:45 by almeekel          #+#    #+#             */
/*   Updated: 2025/08/16 12:50:11 by Mimoulapino      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
	return (create_and_append_token(head, word_value, T_WORD));
}
