/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_processor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 10:21:31 by almeekel          #+#    #+#             */
/*   Updated: 2025/07/23 15:52:20 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

int	process_expansion(t_str_builder *sb, const char **ip, char **envp,
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
