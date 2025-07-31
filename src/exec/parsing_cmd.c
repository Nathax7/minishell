/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:27:37 by nagaudey          #+#    #+#             */
/*   Updated: 2025/07/24 14:02:05 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_files	*append_infile_node(t_files *current, char *value, int heredoc,
		char ***envp_ptr)
{
	t_files	*new_node;
	t_files	*last;

	new_node = new_infile_node(value, heredoc, envp_ptr);
	if (!new_node)
		return (NULL);
	if (!current)
		return (new_node);
	last = find_last_files(current);
	last->next = new_node;
	new_node->prev = last;
	return (current);
}

t_files	*append_outfile_node(t_files *current, char *value, int append)
{
	t_files	*new_node;
	t_files	*last;

	new_node = new_outfile_node(value, append);
	if (!new_node)
		return (NULL);
	if (!current)
		return (new_node);
	last = find_last_files(current);
	last->next = new_node;
	new_node->prev = last;
	return (current);
}

int	is_redirection(t_token **tokens, t_cmd **cmd, char ***envp_ptr)
{
	int	flag;

	if ((*tokens)->type == T_REDIRECT_IN || (*tokens)->type == T_HEREDOC)
	{
		flag = ((*tokens)->type == T_HEREDOC);
		(*tokens) = (*tokens)->next;
		if (!(*tokens) || (*tokens)->type != T_WORD)
			return (1);
		(*cmd)->files = append_infile_node((*cmd)->files, (*tokens)->value,
				flag, envp_ptr);
		(*tokens) = (*tokens)->next;
	}
	else if ((*tokens)->type == T_REDIRECT_OUT || (*tokens)->type == T_APPEND)
	{
		flag = ((*tokens)->type == T_APPEND);
		(*tokens) = (*tokens)->next;
		if (!(*tokens) || (*tokens)->type != T_WORD)
			return (-1);
		(*cmd)->files = append_outfile_node((*cmd)->files, (*tokens)->value,
				flag);
		(*tokens) = (*tokens)->next;
	}
	if ((*cmd)->files == NULL)
		return (1);
	return (0);
}

t_cmd	*parse_commands(t_token **tokens, t_cmd **cmd, char ***envp_ptr)
{
	if (!(*cmd))
		return (NULL);
	while ((*tokens) && (*tokens)->type != T_PIPE)
	{
		if ((*tokens)->type == T_WORD)
		{
			(*cmd)->args = append_args_node((*cmd)->args, (*tokens)->value);
			if ((*cmd)->args == NULL)
				return (NULL);
			(*tokens) = (*tokens)->next;
		}
		else
		{
			if (is_redirection(tokens, cmd, envp_ptr) == 1)
				return (NULL);
		}
		(*cmd)->is_builtin = is_builtin(find_first_args((*cmd)->args));
	}
	return (*cmd);
}

t_cmd	*parsing_cmd(t_token *tokens, char ***envp_ptr)
{
	t_cmd	*cmd;
	t_cmd	*head;

	cmd = append_cmd_node(NULL);
	if (!cmd)
		return (NULL);
	head = cmd;
	while (tokens)
	{
		cmd = parse_commands(&tokens, &cmd, envp_ptr);
		if (!cmd)
			return (free_parsing_cmd(&head));
		if (tokens && tokens->type == T_PIPE)
		{
			tokens = tokens->next;
			cmd = append_cmd_node(cmd);
			if (!cmd)
				return (free_parsing_cmd(&head));
		}
	}
	return (head);
}
