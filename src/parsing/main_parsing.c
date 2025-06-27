/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:31:48 by almeekel          #+#    #+#             */
/*   Updated: 2025/06/23 20:45:30 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

t_token	*process_complete_syntax(t_syntax_result syntax_result, char **envp,
		int exit_status)
{
	t_token	*expanded_tokens;

	expanded_tokens = expand_tokens(syntax_result.tokens, envp, exit_status);
	free_token_list(syntax_result.tokens);
	return (expanded_tokens);
}

static int	check_signal_interruption(void)
{
	if (g_signal_test == 130)
	{
		g_signal_test = 130;
		return (1);
	}
	return (0);
}

t_token	*parse_complete_input(char **accumulated_input, char **envp,
		int exit_status)
{
	char			*line;
	t_token			*tokens;
	t_syntax_result	syntax_result;

	line = *accumulated_input;
	if (check_signal_interruption())
		return (cleanup_parsing_and_return_null(&line, &accumulated_input, NULL, NULL));
	if (has_unclosed_quotes(line))
		return (cleanup_parsing_and_return_null(&line, &accumulated_input, NULL,
				"minishell: syntax error: unclosed quotes\n"));
	tokens = lexer(line);
	if (!tokens)
		return (cleanup_parsing_and_return_null(&line, &accumulated_input, NULL, NULL));
	syntax_result = analyze_syntax(tokens);
	if (syntax_result.status == PARSE_OK)
	{
		*accumulated_input = line;
		return (process_complete_syntax(syntax_result, envp, exit_status));
	}
	else
	{
		handle_syntax_error(&syntax_result);
		return (cleanup_parsing_and_return_null(&line, &accumulated_input, 
				&tokens, NULL));
	}
}
