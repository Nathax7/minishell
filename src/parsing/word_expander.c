/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 10:42:46 by almeekel          #+#    #+#             */
/*   Updated: 2025/08/19 17:57:28 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	create_word_token(t_token **expanded_head, char *value)
{
	if (!create_and_append_token(expanded_head, value, T_WORD))
	{
		free(value);
		return (0);
	}
	return (1);
}

static int	add_field_tokens(char **fields, t_token **expanded_head)
{
	int		i;
	char	*field_copy;

	i = 0;
	while (fields && fields[i])
	{
		field_copy = ft_strdup(fields[i]);
		if (!field_copy)
			return (0);
		if (!create_word_token(expanded_head, field_copy))
			return (0);
		i++;
	}
	return (1);
}

static int	handle_field_split(char *unquoted_value, t_token **expanded_head)
{
	char	**fields;

	fields = perform_field_splitting(unquoted_value, NULL);
	free(unquoted_value);
	if (!fields)
		return (0);
	if (!fields[0])
	{
		ft_freesplit(fields);
		return (1);
	}
	if (!add_field_tokens(fields, expanded_head))
	{
		ft_freesplit(fields);
		return (0);
	}
	ft_freesplit(fields);
	return (1);
}

static int	process_expanded_token(char *expanded_value,
		const char *original_value, t_token **expanded_head)
{
	char		*unquoted_value;
	const char	*p = original_value;

	unquoted_value = remove_outer_quotes(expanded_value);
	if (!unquoted_value)
		return (0);
	if (!*unquoted_value)
	{
		if (token_has_quotes(original_value))
			return (create_word_token(expanded_head, unquoted_value));
		free(unquoted_value);
		return (1);
	}
	if (!should_field_split(original_value))
		return (create_word_token(expanded_head, unquoted_value));
	if (token_has_quotes(original_value))
	{
		while (*p && *p != '=' && *p != '"' && *p != '\'')
			p++;
		if (*p == '=')
			return (create_word_token(expanded_head, unquoted_value));
	}
	return (handle_field_split(unquoted_value, expanded_head));
}

int	process_word_expansion(t_token *token, t_token **expanded_head, char **envp,
		int *exit_status)
{
	char	*expanded_value;
	int		result;

	expanded_value = expand_variables_in_str(token->value, envp, exit_status);
	if (!expanded_value)
		return (0);
	result = process_expanded_token(expanded_value, token->value,
			expanded_head);
	free(expanded_value);
	return (result);
}
