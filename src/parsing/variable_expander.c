/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:08:05 by almeekel          #+#    #+#             */
/*   Updated: 2025/08/19 18:03:04 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	process_single_quotes(t_str_builder *sb, const char **ip)
{
	if (!sb_append_char(sb, '\''))
		return (0);
	(*ip)++;
	while (**ip && **ip != '\'')
	{
		if (!sb_append_char(sb, **ip))
			return (0);
		(*ip)++;
	}
	if (**ip == '\'')
	{
		if (!sb_append_char(sb, '\''))
			return (0);
		(*ip)++;
	}
	return (1);
}

static int	process_double_quote_content(t_str_builder *sb, const char **ip,
		char **envp, int *exit_status)
{
	while (**ip && **ip != '"')
	{
		if (should_expand_variable(**ip, *(*ip + 1)))
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
	return (1);
}

static int	process_double_quotes(t_str_builder *sb, const char **ip,
		char **envp, int *exit_status)
{
	if (!sb_append_char(sb, '"'))
		return (0);
	(*ip)++;
	if (!process_double_quote_content(sb, ip, envp, exit_status))
		return (0);
	if (**ip == '"')
	{
		if (!sb_append_char(sb, '"'))
			return (0);
		(*ip)++;
	}
	return (1);
}

static int	process_current_char(t_str_builder *sb, const char **ip,
		char **envp, int *exit_status)
{
	if (**ip == '\'')
		return (process_single_quotes(sb, ip));
	else if (**ip == '"')
		return (process_double_quotes(sb, ip, envp, exit_status));
	else if (**ip == '$' && *(*ip + 1) == '"')
		return (process_expansion(sb, ip, envp, exit_status));
	else if (**ip == '$' && *(*ip + 1) == '\'')
		return (process_expansion(sb, ip, envp, exit_status));
	else if (should_expand_variable(**ip, *(*ip + 1)))
		return (process_expansion(sb, ip, envp, exit_status));
	else
		return (process_regular_char(sb, ip));
}

char	*expand_variables_in_str(const char *input_str, char **envp,
		int *exit_status)
{
	t_str_builder	sb;
	const char		*ip;

	if (!input_str)
		return (NULL);
	sb_init(&sb);
	ip = input_str;
	while (*ip)
	{
		if (!process_current_char(&sb, &ip, envp, exit_status))
			return (sb_free_and_return_null(&sb));
	}
	return (sb_to_string_and_free(&sb));
}
