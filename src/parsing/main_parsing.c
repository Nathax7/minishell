/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:31:48 by almeekel          #+#    #+#             */
/*   Updated: 2025/06/03 10:57:47 by almeekel         ###   ########.fr       */
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

char	*accumulate_input(char *existing, char *new_input)
{
	char	*combined;
	char	*final;

	if (!existing)
		return (ft_strdup(new_input));
	if (!new_input)
		return (existing);
	combined = ft_strjoin(existing, " ");
	if (!combined)
	{
		free(existing);
		return (NULL);
	}
	final = ft_strjoin(combined, new_input);
	free(combined);
	free(existing);
	return (final);
}

t_token	*process_complete_syntax(t_syntax_result syntax_result, char **envp, int exit_status)
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

	new_line = secure_readline(get_continuation_prompt(syntax_result->next_prompt));
	if (!new_line)
	{
		free_token_list(syntax_result->tokens);
		if (syntax_result->error_token)
			free(syntax_result->error_token);
		return (0);
	}
	updated_line = accumulate_input(*line, new_line);
	free(new_line);
	if (!updated_line)
		return (0);
	*line = updated_line;
	return (1);
}

t_token	*parse_complete_input(char **accumulated_input, char **envp, int exit_status)
{
	char *line;
	t_token *tokens;
	t_syntax_result syntax_result;
	t_token *result;

	line = *accumulated_input;
	while (1)
	{
		if (has_unclosed_quotes(line))
		{
			result = handle_quote_incomplete(&line, &accumulated_input);
			if (result != (t_token *)1)
				return (result);
			continue ;
		}
		tokens = lexer(line);
		if (!tokens)
			return (handle_lexer_failure(&line, &accumulated_input));

		syntax_result = analyze_syntax(tokens);
		if (syntax_result.status == PARSE_OK)
			return (handle_syntax_success(&line, &accumulated_input,
					&syntax_result, envp, exit_status));
		else if (syntax_result.status == PARSE_SYNTAX_ERROR)
			return (handle_syntax_error_case(&line, &accumulated_input,
					&syntax_result));
		else
		{
			result = handle_incomplete_case(&line, &accumulated_input,
					&syntax_result, tokens);
			if (result != (t_token *)1)
				return (result);
		}
	}
}
