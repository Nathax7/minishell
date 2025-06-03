/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:08:05 by almeekel          #+#    #+#             */
/*   Updated: 2025/05/29 16:28:07 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static char	*process_variable_expansion(const char **str_ptr, char **envp,
		int last_exit_status)
{
	const char		*start;
	char			*var_name;
	char			*var_value;
	t_str_builder	var_name_sb;

	(*str_ptr)++;
	if (**str_ptr == '?')
	{
		(*str_ptr)++;
		return (get_env_var_value("?", envp, last_exit_status));
	}
	if (**str_ptr == '{')
	{
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
			return (var_name ? var_name : ft_strdup("${"));
		}
	}
	else
	{
		sb_init(&var_name_sb);
		while (is_valid_var_char(**str_ptr))
		{
			sb_append_char(&var_name_sb, **str_ptr);
			(*str_ptr)++;
		}
		var_name = sb_to_string_and_free(&var_name_sb);
	}
	if (!var_name)
		return (ft_strdup("$"));
	var_value = get_env_var_value(var_name, envp, last_exit_status);
	free(var_name);
	return (var_value);
}

char	*expand_variables_in_str(const char *input_str, t_quote quote_type,
		char **envp, int last_exit_status)
{
	t_str_builder	sb;
	const char		*ip;
	char			*expanded_part;

	if (!input_str)
		return (NULL);
	sb_init(&sb);
	ip = input_str;
	while (*ip)
	{
		if (*ip == '$' && quote_type != Q_SINGLE && (is_valid_var_char(*(ip
						+ 1)) || *(ip + 1) == '?' || *(ip + 1) == '{'))
		{
			expanded_part = process_variable_expansion(&ip, envp,
					last_exit_status);
			if (expanded_part)
			{
				if (!sb_append_str(&sb, expanded_part))
				{
					free(expanded_part);
					return (sb_free_and_return_null(&sb));
				}
				free(expanded_part);
			}
		}
		else
		{
			if (!sb_append_char(&sb, *ip))
				return (sb_free_and_return_null(&sb));
			ip++;
		}
	}
	return (sb_to_string_and_free(&sb));
}
