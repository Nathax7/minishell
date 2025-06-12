/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing_core.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:35:07 by almeekel          #+#    #+#             */
/*   Updated: 2025/06/12 18:58:03 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

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

