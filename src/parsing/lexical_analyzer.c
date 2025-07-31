/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyzer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 18:20:29 by almeekel          #+#    #+#             */
/*   Updated: 2025/07/23 15:52:30 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	process_operator(const char **line, t_token **head)
{
	if (**line == '|')
		return (handle_pipe_operator(line, head));
	else if (**line == '<')
		return (handle_lesser_operator(line, head));
	else if (**line == '>')
		return (handle_greater_operator(line, head));
	return (0);
}

int	has_content(const char *line)
{
	while (*line)
	{
		if (!ft_isspace(*line))
			return (1);
		line++;
	}
	return (0);
}

t_token	*lexer(const char *line)
{
	t_token	*head;
	int		status;

	if (!line || !has_content(line))
		return (NULL);
	if (has_unclosed_quotes(line))
		return (NULL);
	head = NULL;
	while (*line)
	{
		while (ft_isspace(*line))
			line++;
		if (!*line)
			break ;
		if (is_operator_start(*line))
			status = process_operator(&line, &head);
		else
			status = process_word(&line, &head);
		if (!status)
		{
			free_token_list(head);
			return (NULL);
		}
	}
	return (head);
}
