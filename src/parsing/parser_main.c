/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:31:48 by almeekel          #+#    #+#             */
/*   Updated: 2025/07/30 17:25:20 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token	*process_complete_syntax(t_syntax_result syntax_result, char **envp,
		int exit_status)
{
	t_token	*expanded_tokens;

	expanded_tokens = expand_tokens(syntax_result.tokens, envp, exit_status);
	free_token_list(syntax_result.tokens);
	syntax_result.tokens = NULL;
	return (expanded_tokens);
}

static int	check_signal_interruption(void)
{
	if (g_signal_status == 130)
	{
		g_signal_status = 130;
		return (1);
	}
	return (0);
}

static t_token	*handle_initial_checks(char *line)
{
	if (check_signal_interruption())
		return (cleanup_parsing_and_return_null(NULL, NULL));
	if (has_unclosed_quotes(line))
		return (cleanup_parsing_and_return_null(NULL,
				"minishell: syntax error: unclosed quotes\n"));
	return ((t_token *)1);
}

static t_token	*handle_syntax_processing(t_syntax_result *syntax_result,
		char **envp, int *exit_status)
{
	if (syntax_result->status == PARSE_OK)
	{
		if (handle_syntax_success(syntax_result, envp,
				*exit_status) == PARSE_SUCCESS)
			return (syntax_result->expanded_tokens);
		return (cleanup_parsing_and_return_null(syntax_result, NULL));
	}
	else
	{
		handle_syntax_error(syntax_result);
		*exit_status = 2;
		return (cleanup_parsing_and_return_null(syntax_result, NULL));
	}
}

t_token	*parse_complete_input(char *line, char **envp, int *exit_status)
{
	t_token			*tokens;
	t_syntax_result	syntax_result;
	t_token			*check_result;

	check_result = handle_initial_checks(line);
	if (check_result != (t_token *)1)
		return (check_result);
	tokens = lexer(line);
	if (!tokens)
		return (cleanup_parsing_and_return_null(NULL, NULL));
	printf("\n=== DEBUG: Tokens after lexical analysis ===\n");
	print_token_list(tokens);
	printf("============================================\n\n");
	syntax_result = analyze_syntax(tokens);
	return (handle_syntax_processing(&syntax_result, envp, exit_status));
}
