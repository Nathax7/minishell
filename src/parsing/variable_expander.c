/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:08:05 by almeekel          #+#    #+#             */
/*   Updated: 2025/07/31 14:03:21 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	should_expand_variable(char current_char, char next_char,
		t_quote quote_type)
{
	if (current_char != '$')
		return (0);
	if (quote_type == Q_SINGLE)
		return (0);
	if (is_valid_var_char(next_char) || next_char == '?' || next_char == '{')
		return (1);
	return (0);
}

static int	process_regular_char(t_str_builder *sb, const char **ip)
{
	if (!sb_append_char(sb, **ip))
		return (0);
	(*ip)++;
	return (1);
}

static int	process_quoted_expansion_single(t_str_builder *sb, const char **ip,
		char **envp, int exit_status)
{
	t_quote	quote_type;

	quote_type = Q_SINGLE;
	if (!sb_append_char(sb, '\''))
		return (0);
	(*ip)++;
	while (**ip && **ip != '\'')
	{
		if (should_expand_variable(**ip, *(*ip + 1), quote_type))
		{
			if (!process_expansion(sb, ip, envp, exit_status))
				return (0);
		}
		else if (*(*ip + 1) == '"' || *(*ip + 1) == '\\' || *(*ip + 1) == '\n')
		{
			(*ip)++;
			if (!sb_append_char(sb, **ip))
				return (0);
			(*ip)++;
		}
		else
		{
			if (!process_regular_char(sb, ip))
				return (0);
		}
	}
	if (**ip == '\'')
	{
		if (!sb_append_char(sb, '\''))
			return (0);
		(*ip)++;
	}
	return (1);
}

static int	process_quoted_expansion_double(t_str_builder *sb, const char **ip,
		char **envp, int exit_status)
{
	t_quote	quote_type;

	quote_type = Q_DOUBLE;
	if (!sb_append_char(sb, '"'))
		return (0);
	(*ip)++;
	while (**ip && **ip != '"')
	{
		if (should_expand_variable(**ip, *(*ip + 1), quote_type))
		{
			if (!process_expansion(sb, ip, envp, exit_status))
				return (0);
		}
		else if (**ip == '\\' && (*(*ip + 1) == '$' || *(*ip + 1) == '"'
				|| *(*ip + 1) == '\\' || *(*ip + 1) == '\n'))
		{
			(*ip)++;
			if (!sb_append_char(sb, **ip))
				return (0);
			(*ip)++;
		}
		else
		{
			if (!process_regular_char(sb, ip))
				return (0);
		}
	}
	if (**ip == '"')
	{
		if (!sb_append_char(sb, '"'))
			return (0);
		(*ip)++;
	}
	return (1);
}

char	*expand_variables_in_str(const char *input_str, char **envp,
		int last_exit_status)
{
	t_str_builder	sb;
	const char		*ip;
	char			*result;

	if (!input_str)
		return (NULL);
	sb_init(&sb);
	ip = input_str;
	while (*ip)
	{
		if (*ip == '\'')
		{
			if (!process_quoted_expansion_single(&sb, &ip, envp,
					last_exit_status))
				return (sb_free_and_return_null(&sb));
		}
		if (*ip == '"')
		{
			if (!process_quoted_expansion_double(&sb, &ip, envp,
					last_exit_status))
				return (sb_free_and_return_null(&sb));
		}
		else if (should_expand_variable(*ip, *(ip + 1), Q_NONE))
		{
			if (!process_expansion(&sb, &ip, envp, last_exit_status))
				return (sb_free_and_return_null(&sb));
		}
		else
		{
			if (!process_regular_char(&sb, &ip))
				return (sb_free_and_return_null(&sb));
		}
	}
	result = sb_to_string_and_free(&sb);
	return (result);
}
