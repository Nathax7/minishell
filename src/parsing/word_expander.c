/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 10:42:46 by almeekel          #+#    #+#             */
/*   Updated: 2025/07/31 16:36:33 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	handle_empty_expansion(char *expanded_value, t_token *token,
		t_token **expanded_head)
{
	if (!*expanded_value && token->quote != Q_NONE)
	{
		if (!create_and_append_token(expanded_head, expanded_value, T_WORD,
				Q_NONE))
		{
			free(expanded_value);
			return (0);
		}
		return (1);
	}
	if (!*expanded_value)
	{
		free(expanded_value);
		return (1);
	}
	return (-1);
}

static int	handle_quoted_expansion(char *expanded_value,
		t_token **expanded_head)
{
	char	*final_value;

	final_value = remove_outer_quotes(expanded_value);
	free(expanded_value);
	if (!final_value)
		return (0);
	if (!create_and_append_token(expanded_head, final_value, T_WORD))
	{
		free(final_value);
		return (0);
	}
	return (1);
}

static int	add_expanded_tokens(char **fields, t_token **head)
{
	int		i;
	char	*field_copy;

	i = 0;
	while (fields && fields[i])
	{
		field_copy = ft_strdup(fields[i]);
		if (!field_copy)
			return (0);
		if (!create_and_append_token(head, field_copy, T_WORD, Q_NONE))
		{
			free(field_copy);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	handle_field_split_expansion(char *expanded_value,
		t_token **expanded_head)
{
	char	**fields;
	char	*unquoted_value;

	unquoted_value = remove_outer_quotes(expanded_value);
	free(expanded_value);
	if (!unquoted_value)
		return (0);
	fields = perform_field_splitting(unquoted_value, NULL);
	free(unquoted_value);
	if (!fields)
		return (0);
	if (!fields[0])
	{
		ft_freesplit(fields);
		return (1);
	}
	if (!add_expanded_tokens(fields, expanded_head))
	{
		ft_freesplit(fields);
		return (0);
	}
	ft_freesplit(fields);
	return (1);
}

int	process_word_expansion(t_token *token, t_token **expanded_head, char **envp,
		int exit_status)
{
	char	*expanded_value;
	int		empty_result;

	expanded_value = expand_token_value(token->value, token->quote, envp,
			exit_status);
	if (!expanded_value)
		return (0);
	empty_result = handle_empty_expansion(expanded_value, token, expanded_head);
	if (empty_result != -1)
		return (empty_result);
	if (!should_field_split(token->quote))
		return (handle_quoted_expansion(expanded_value, expanded_head));
	return (handle_field_split_expansion(expanded_value, expanded_head));
}
int	process_word_expansion(t_token *token, t_token **expanded_head, char **envp,
		int exit_status)
{
	char	*expanded_value;
	int		empty_result;

	expanded_value = expand_heredoc_line(token->value, envp, exit_status);
	printf("%s/n", expanded_value);
	if (!expanded_value)
		return (0);
	empty_result = handle_empty_expansion(expanded_value, token, expanded_head);
	if (empty_result != -1)
		return (empty_result);
	if (!should_field_split(token->quote))
		return (handle_quoted_expansion(expanded_value, expanded_head));
	return (handle_field_split_expansion(expanded_value, expanded_head));
}
