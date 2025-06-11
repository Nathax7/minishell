/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing_core.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:35:07 by almeekel          #+#    #+#             */
/*   Updated: 2025/06/04 16:02:52 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

t_parse_result	handle_quote_incomplete(char **line, char ***accumulated_input)
{
	if (!handle_quote_continuation(line))
	{
		free(*line);
		**accumulated_input = NULL;
		return (PARSE_ERROR);
	}
	return (PARSE_CONTINUE);
}

t_parse_result	handle_lexer_failure(char **line, char ***accumulated_input)
{
	free(*line);
	**accumulated_input = NULL;
	return (PARSE_ERROR);
}

t_parse_result	handle_syntax_success(char **line, char ***accumulated_input,
		t_syntax_result *result, char **envp, int exit_status,
		t_token **tokens_out)
{
	**accumulated_input = *line;
	*tokens_out = process_complete_syntax(*result, envp, exit_status);
	if (*tokens_out)
		return (PARSE_SUCCESS);
	return (PARSE_ERROR);
}

t_parse_result	handle_syntax_error_case(char **line, char ***accumulated_input,
		t_syntax_result *result)
{
	handle_syntax_error(result);
	free(*line);
	**accumulated_input = NULL;
	return (PARSE_ERROR);
}

t_parse_result	handle_incomplete_case(char **line, char ***accumulated_input,
		t_syntax_result *result, t_token *tokens)
{
	if (!handle_incomplete_input(line, result))
	{
		**accumulated_input = NULL;
		return (PARSE_ERROR);
	}
	free_token_list(tokens);
	if (result->error_token)
	{
		free(result->error_token);
		result->error_token = NULL;
	}
	return (PARSE_CONTINUE);
}
