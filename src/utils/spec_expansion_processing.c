/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_expansion_processing.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:53:46 by almeekel          #+#    #+#             */
/*   Updated: 2025/08/19 17:54:32 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*process_question_mark_expansion(const char **str_ptr, char **envp,
		int *last_exit_status)
{
	(*str_ptr)++;
	return (get_env_var_value("?", envp, last_exit_status));
}

char	*process_accolades_expansion(const char **str_ptr)
{
	const char	*start;
	char		*var_name;

	(*str_ptr)++;
	start = *str_ptr;
	while (**str_ptr && **str_ptr != '}')
		(*str_ptr)++;
	if (**str_ptr == '}')
	{
		if (*str_ptr == start)
			var_name = ft_strdup("");
		else
			var_name = ft_substr(start, 0, *str_ptr - start);
		(*str_ptr)++;
	}
	else
	{
		var_name = ft_substr(start - 2, 0, *str_ptr - start + 2);
		return (ft_strdup("${"));
	}
	return (var_name);
}

char	*process_regular_variable_expansion(const char **str_ptr)
{
	t_str_builder	var_name_sb;
	char			*var_name;

	sb_init(&var_name_sb);
	while (is_valid_var_char(**str_ptr))
	{
		sb_append_char(&var_name_sb, **str_ptr);
		(*str_ptr)++;
	}
	var_name = sb_to_string_and_free(&var_name_sb);
	return (var_name);
}

int	token_has_quotes(const char *token_value)
{
	if (!token_value)
		return (0);
	while (*token_value)
	{
		if (*token_value == '\'' || *token_value == '"')
			return (1);
		token_value++;
	}
	return (0);
}

int	should_field_split(const char *token_value)
{
	int	in_single_quote;
	int	in_double_quote;

	if (!token_value)
		return (1);
	in_single_quote = 0;
	in_double_quote = 0;
	while (*token_value)
	{
		if (*token_value == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (*token_value == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (!in_single_quote && !in_double_quote)
			return (1);
		token_value++;
	}
	return (0);
}
