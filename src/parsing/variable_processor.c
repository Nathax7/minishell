/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_processor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 10:21:31 by almeekel          #+#    #+#             */
/*   Updated: 2025/08/19 16:10:06 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*extract_single_quoted_content(const char **str_ptr)
{
	const char	*start;
	const char	*p;
	char		*var_name;

	start = *str_ptr + 1;
	p = start;
	while (*p && *p != '\'')
		p++;
	var_name = ft_substr(start, 0, p - start);
	if (*p == '\'')
		*str_ptr = p + 1;
	else
		*str_ptr = p;
	return (var_name);
}

static char	*extract_double_quoted_content(const char **str_ptr)
{
	const char	*start;
	const char	*p;
	char		*var_name;

	start = *str_ptr + 1;
	p = start;
	while (*p && *p != '"')
		p++;
	var_name = ft_substr(start, 0, p - start);
	if (*p == '"')
		*str_ptr = p + 1;
	else
		*str_ptr = p;
	return (var_name);
}

static char	*process_variable_expansion(const char **str_ptr, char **envp,
		int *last_exit_status)
{
	char	*var_name;
	char	*var_value;

	(*str_ptr)++;
	if (**str_ptr == '\0')
		return (ft_strdup("$"));
	if (**str_ptr == '\'')
		return (extract_single_quoted_content(str_ptr));
	if (**str_ptr == '"')
		return (extract_double_quoted_content(str_ptr));
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
		int *last_exit_status)
{
	char	*expanded_part;

	expanded_part = process_variable_expansion(ip, envp, last_exit_status);
	if (expanded_part)
	{
		if (*expanded_part == '\0')
		{
			free(expanded_part);
			return (1);
		}
		if (!sb_append_str(sb, expanded_part))
		{
			free(expanded_part);
			return (0);
		}
		free(expanded_part);
	}
	return (1);
}
