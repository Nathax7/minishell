/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing_core.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:35:07 by almeekel          #+#    #+#             */
/*   Updated: 2025/05/28 16:19:16 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

t_token	*handle_quote_incomplete(char **line, char ***accumulated_input)
{
	if (!handle_quote_continuation(line))
	{
		free(*line);
		**accumulated_input = NULL;
		return (NULL);
	}
	return ((t_token *)1);
}

t_token	*handle_lexer_failure(char **line, char ***accumulated_input)
{
	free(*line);
	**accumulated_input = NULL;
	return (NULL);
}

t_token	*handle_syntax_success(char **line, char ***accumulated_input, 
		t_syntax_result *result, char **envp, int exit_status)
{
	**accumulated_input = *line;
	return (process_complete_syntax(*result, envp, exit_status));
}

t_token	*handle_syntax_error_case(char **line,
		char ***accumulated_input, t_syntax_result *result)
{
	handle_syntax_error(result);
	free(*line);
	**accumulated_input = NULL;
	return (NULL);
}

t_token	*handle_incomplete_case(char **line, char ***accumulated_input,
		t_syntax_result *result, t_token *tokens)
{
	if (!handle_incomplete_input(line, result))
	{
		**accumulated_input = NULL;
		return (NULL);
	}
	free_token_list(tokens);
	if (result->error_token)
	{
		free(result->error_token);
		result->error_token = NULL;
	}
	return ((t_token *)1);
}