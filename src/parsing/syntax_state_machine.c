/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_state_machine.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:38:32 by almeekel          #+#    #+#             */
/*   Updated: 2025/06/30 20:03:58 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	validate_pipe_sequence(t_token *tokens, char **error_token)
{
	t_token	*current;
	int		has_command;

	current = tokens;
	has_command = 0;
	while (current)
	{
		if (current->type == T_WORD)
			has_command = 1;
		else if (current->type == T_PIPE)
		{
			if (!has_command)
			{
				*error_token = ft_strdup(current->value);
				return (0);
			}
			if (!current->next)
				return (2);
			has_command = 0;
		}
		current = current->next;
	}
	return (1);
}

static int	validate_redirections(t_token *tokens, char **error_token)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == T_REDIRECT_IN || current->type == T_REDIRECT_OUT
			|| current->type == T_APPEND || current->type == T_HEREDOC)
		{
			if (!current->next)
			{
				*error_token = ft_strdup("newline");
				return (0);
			}
			if (current->next->type != T_WORD)
			{
				*error_token = ft_strdup(current->next->value);
				return (0);
			}
			current = current->next;
		}
		current = current->next;
	}
	return (1);
}

t_syntax_result	analyze_syntax(t_token *tokens)
{
	t_syntax_result	result;
	char			*error_token;
	int				pipe_status;
	int				redirect_status;

	result.tokens = tokens;
	result.error_token = NULL;
	result.status = PARSE_OK;
	error_token = NULL;
	pipe_status = validate_pipe_sequence(tokens, &error_token);
	if (pipe_status == 0)
	{
		result.status = PARSE_SYNTAX_ERROR;
		result.error_token = error_token;
		return (result);
	}
	else if (pipe_status == 2)
	{
		result.status = PARSE_SYNTAX_ERROR;
		result.error_token = ft_strdup("newline");
		return (result);
	}
	redirect_status = validate_redirections(tokens, &error_token);
	if (redirect_status == 0)
	{
		result.status = PARSE_SYNTAX_ERROR;
		result.error_token = error_token;
		return (result);
	}
	return (result);
}
