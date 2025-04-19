/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:02:41 by almeekel          #+#    #+#             */
/*   Updated: 2025/04/19 19:34:07 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// parser.c
#include "../../includes/parsing.h"

static t_cmd	*new_cmd_node(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = 0;
	cmd->heredoc = 0;
	cmd->heredoc_delim = NULL;
	cmd->next = NULL;
	return (cmd);
}

static int	add_arg(t_cmd *cmd, char *arg)
{
	int		count;
	char	**new_args;

	count = 0;
	while (cmd->args && cmd->args[count])
		count++;
	new_args = malloc(sizeof(char *) * (count + 2));
	if (!new_args)
		return (0);
	for (int i = 0; i < count; i++)
		new_args[i] = cmd->args[i];
	new_args[count] = arg;
	new_args[count + 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
	return (1);
}

static int	parse_redirection(t_cmd *cmd, t_token **tokens)
{
	t_token	*curr;
	char	*filename;

	curr = *tokens;
	if (!curr->next || curr->next->type != T_WORD)
		return (0);
	filename = curr->next->value;
	if (curr->type == T_REDIRECT_IN)
		cmd->infile = filename;
	else if (curr->type == T_REDIRECT_OUT)
	{
		cmd->outfile = filename;
		cmd->append = 0;
	}
	else if (curr->type == T_APPEND)
	{
		cmd->outfile = filename;
		cmd->append = 1;
	}
	else if (curr->type == T_HEREDOC)
	{
		cmd->heredoc = 1;
		cmd->heredoc_delim = filename;
	}
	*tokens = curr->next; // skip both tokens
	return (1);
}

t_cmd	*build_command_list(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*curr_cmd;
	t_cmd	*tmp;

	head = NULL;
	curr_cmd = NULL;
	while (tokens)
	{
		if (!curr_cmd)
		{
			curr_cmd = new_cmd_node();
			if (!head)
				head = curr_cmd;
			else
			{
				tmp = head;
				while (tmp->next)
					tmp = tmp->next;
				tmp->next = curr_cmd;
			}
		}
		if (tokens->type == T_WORD)
			add_arg(curr_cmd, tokens->value);
		else if (tokens->type == T_REDIRECT_IN || tokens->type == T_REDIRECT_OUT
			|| tokens->type == T_APPEND || tokens->type == T_HEREDOC)
		{
			if (!parse_redirection(curr_cmd, &tokens))
				return (NULL);
		}
		else if (tokens->type == T_PIPE)
			curr_cmd = NULL;
		tokens = tokens->next;
	}
	return (head);
}
