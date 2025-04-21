/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 21:31:30 by nagaudey          #+#    #+#             */
/*   Updated: 2025/04/21 21:35:26 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

t_cmd *new_node(t_type type, char *file, char **cmd_args)
{
	t_cmd *node = malloc(sizeof(t_cmd));
	if (!node)
		return NULL;
	node->type = type;
	node->file = file ? strdup(file) : NULL;
	node->cmd_args = cmd_args;
	node->limiter = NULL;
	node->next = NULL;
	return node;
}

t_cmd *parse_line(char *line)
{
	char **tokens = ft_split_whitespace(line); // ex: ["<", "b", "cat", "|", "rev", ">", "b"]
	t_cmd *head = NULL, *last = NULL;
	int i = 0;

	while (tokens[i])
	{
		t_cmd *node = NULL;

		if (strcmp(tokens[i], "<") == 0 && tokens[i + 1])
			node = new_node(INFILE, tokens[++i], NULL);
		else if (strcmp(tokens[i], ">") == 0 && tokens[i + 1])
			node = new_node(OUTFILE, tokens[++i], NULL);
		else if (strcmp(tokens[i], ">>") == 0 && tokens[i + 1])
			node = new_node(APPEND, tokens[++i], NULL);
		else if (strcmp(tokens[i], "<<") == 0 && tokens[i + 1])
		{
			node = new_node(HEREDOC, NULL, NULL);
			node->limiter = strdup(tokens[++i]);
		}
		else if (strcmp(tokens[i], "|") == 0)
		{
			// Do nothing (pipe just separates commands)
		}
		else
		{
			node = new_node(CMD, NULL, ft_split(tokens[i], ' '));
		}

		if (node)
		{
			if (!head)
				head = node;
			else
				last->next = node;
			last = node;
		}
		i++;
	}
	// free tokens if needed
	return head;
}
