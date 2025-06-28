/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:08:05 by almeekel          #+#    #+#             */
/*   Updated: 2025/06/28 17:55:45 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static char	*process_question_mark_expansion(const char **str_ptr, char **envp,
		int last_exit_status)
{
	(*str_ptr)++;
	return (get_env_var_value("?", envp, last_exit_status));
}

static char	*process_accolades_expansion(const char **str_ptr)
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

static char	*process_regular_variable_expansion(const char **str_ptr)
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

static char	*process_variable_expansion(const char **str_ptr, char **envp,
		int last_exit_status)
{
	char	*var_name;
	char	*var_value;

	(*str_ptr)++;
	if (**str_ptr == '?')
		return (process_question_mark_expansion(str_ptr, envp,
				last_exit_status));
	if (**str_ptr == '{')
		var_name = process_accolades_expansion(str_ptr);
	else
		var_name = process_regular_variable_expansion(str_ptr);
	if (!var_name)
		return (ft_strdup("$"));
	var_value = get_env_var_value(var_name, envp, last_exit_status);
	free(var_name);
	return (var_value);
}

static int	should_expand_variable(char current_char, char next_char,
		t_quote quote_type)
{
	if (current_char != '$')
		return (0);
	if (quote_type == Q_SINGLE)
		return (0);
	if (is_valid_var_char(next_char) || next_char == '?' || next_char == '{')
	{
		return (1);
	}
	return (0);
}

static int	process_expansion(t_str_builder *sb, const char **ip, char **envp,
		int last_exit_status)
{
	char	*expanded_part;

	expanded_part = process_variable_expansion(ip, envp, last_exit_status);
	if (expanded_part)
	{
		if (!sb_append_str(sb, expanded_part))
		{
			free(expanded_part);
			return (0);
		}
		free(expanded_part);
	}
	return (1);
}

static int	process_regular_char(t_str_builder *sb, const char **ip)
{
	if (!sb_append_char(sb, **ip))
		return (0);
	(*ip)++;
	return (1);
}

char	*expand_variables_in_str(const char *input_str, t_quote quote_type,
		char **envp, int last_exit_status)
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
		if (should_expand_variable(*ip, *(ip + 1), quote_type))
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
