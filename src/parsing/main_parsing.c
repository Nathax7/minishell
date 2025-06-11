/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:31:48 by almeekel          #+#    #+#             */
/*   Updated: 2025/06/11 16:55:46 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

char	*get_continuation_prompt(t_prompt_type type)
{
	if (type == PROMPT_PIPE)
		return ("pipe> ");
	else if (type == PROMPT_QUOTE)
		return ("quote> ");
	else if (type == PROMPT_REDIR)
		return ("redir> ");
	else if (type == PROMPT_HEREDOC)
		return ("heredoc> ");
	return ("minishell$ ");
}

t_token	*process_complete_syntax(t_syntax_result syntax_result, char **envp,
		int exit_status)
{
	t_token	*expanded_tokens;

	expanded_tokens = expand_tokens(syntax_result.tokens, envp, exit_status);
	free_token_list(syntax_result.tokens);
	return (expanded_tokens);
}

int	handle_incomplete_input(char **line, t_syntax_result *syntax_result)
{
	char	*new_line;
	char	*updated_line;

	new_line = readline(get_continuation_prompt(syntax_result->next_prompt));
	if (!new_line)
	{
		if (g_signal_test == 130)
		{
			free_token_list(syntax_result->tokens);
			if (syntax_result->error_token)
				free(syntax_result->error_token);
			return (0);
		}
		free_token_list(syntax_result->tokens);
		if (syntax_result->error_token)
			free(syntax_result->error_token);
		return (0);
	}
	if (!*new_line && g_signal_test == 130)
	{
		free(new_line);
		free_token_list(syntax_result->tokens);
		if (syntax_result->error_token)
			free(syntax_result->error_token);
		return (0);
	}
	updated_line = ft_strjoin_space(*line, new_line);
	free(new_line);
	if (!updated_line)
		return (0);
	free(*line);
	*line = updated_line;
	return (1);
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
	t_parse_result	status;
	int				parsing_done;

	line = *accumulated_input;
	parsing_done = 0;
	
	while (!parsing_done)
	{
		if (check_signal_interruption())
		{
			free(line);
			*accumulated_input = NULL;
			return (NULL);
		}
		if (has_unclosed_quotes(line))
		{
			status = handle_quote_incomplete(&line, &accumulated_input);
			if (status == PARSE_ERROR)
			{
				parsing_done = 1;
				return (NULL);
			}
		}
		else
		{
			tokens = lexer(line);
			if (!tokens)
			{
				handle_lexer_failure(&line, &accumulated_input);
				parsing_done = 1;
				return (NULL);
			}
			syntax_result = analyze_syntax(tokens);
			if (syntax_result.status == PARSE_OK)
			{
				status = handle_syntax_success(&line, &accumulated_input,
						&syntax_result, envp, exit_status, &tokens);
				parsing_done = 1;
				if (status == PARSE_SUCCESS)
					return (tokens);
				return (NULL);
			}
			else if (syntax_result.status == PARSE_SYNTAX_ERROR)
			{
				handle_syntax_error_case(&line, &accumulated_input, &syntax_result);
				parsing_done = 1;
				return (NULL);
			}
			else
			{
				status = handle_incomplete_case(&line, &accumulated_input,
						&syntax_result, tokens);
				if (status == PARSE_ERROR)
				{
					parsing_done = 1;
					return (NULL);
				}
			}
		}
	}
	return (NULL);
}
