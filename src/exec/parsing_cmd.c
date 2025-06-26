/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:27:37 by nagaudey          #+#    #+#             */
/*   Updated: 2025/06/25 19:58:01 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_cmd	*append_cmd_node(t_cmd *node)
{
	t_cmd	*new_node;

	new_node = malloc(sizeof(*new_node));
	if (!new_node)
		return (NULL);
	new_node->args = NULL;
	new_node->cmd_path = NULL;
	new_node->files = NULL;
	new_node->is_builtin = 0;
	new_node->fd_input = -1;
	new_node->fd_output = -1;
	new_node->next = NULL;
	new_node->prev = NULL;
	if (!node)
		return (new_node);
	node = find_last_cmd(node);
	node->next = new_node;
	new_node->prev = node;
	return (new_node);
}

t_args	*new_args_node(char *value)
{
	t_args	*new_node;

	new_node = malloc(sizeof(t_args));
	if (!new_node)
		return (NULL);
	new_node->cmd_args = ft_strdup(value);
	if (!new_node->cmd_args)
	{
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

t_args	*append_args_node(t_args *current, char *value)
{
	t_args	*new_node;
	t_args	*last;

	new_node = new_args_node(value);
	if (!new_node)
		return (NULL);
	if (!current)
		return (new_node);
	last = find_last_args(current);
	last->next = new_node;
	new_node->prev = last;
	return (current);
}

t_files	*new_infile_node(char *value, int heredoc)
{
	t_files	*new_node;

	new_node = malloc(sizeof(t_files));
	if (!new_node)
		return (NULL);
	if (heredoc)
		new_node->infile_name = here_doc(new_node, value);
	else
		new_node->infile_name = ft_strdup(value);
	if (!new_node->infile_name)
	{
		free(new_node);
		return (NULL);
	}
	new_node->outfile_name = NULL;
	new_node->heredoc = heredoc;
	new_node->append = 0;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

t_files	*new_outfile_node(char *value, int append)
{
	t_files	*new_node;

	new_node = malloc(sizeof(t_files));
	if (!new_node)
		return (NULL);
	new_node->outfile_name = ft_strdup(value);
	new_node->infile_name = NULL;
	new_node->append = append;
	new_node->heredoc = 0;
	if (!new_node->outfile_name)
	{
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

t_files	*append_infile_node(t_files *current, char *value, int heredoc)
{
	t_files	*new_node;
	t_files	*last;

	new_node = new_infile_node(value, heredoc);
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

int	is_redirection(t_token **tokens, t_cmd **cmd)
{
	int	flag;

	if ((*tokens)->type == T_REDIRECT_IN || (*tokens)->type == T_HEREDOC)
	{
		flag = ((*tokens)->type == T_HEREDOC);
		(*tokens) = (*tokens)->next;
		if (!(*tokens) || (*tokens)->type != T_WORD)
			return (1);
		(*cmd)->files = append_infile_node((*cmd)->files, (*tokens)->value,
				flag);
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

int	is_builtin_cmd(t_args *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd->cmd_args, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd->cmd_args, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd->cmd_args, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd->cmd_args, "export") == 0)
		return (1);
	if (ft_strcmp(cmd->cmd_args, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd->cmd_args, "env") == 0)
		return (1);
	if (ft_strcmp(cmd->cmd_args, "exit") == 0)
		return (1);
	return (0);
}

t_cmd	*parse_commands(t_token **tokens, t_cmd **cmd)
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
			if (is_redirection(tokens, cmd) == 1)
				return (NULL);
		}
		(*cmd)->is_builtin = is_builtin_cmd(find_first_args((*cmd)->args));
	}
	return (*cmd);
}

t_cmd	*parsing_cmd(t_token *tokens)
{
	t_cmd	*cmd;
	t_cmd	*head;

	cmd = append_cmd_node(NULL);
	if (!cmd)
		return (NULL);
	head = cmd;
	while (tokens)
	{
		cmd = parse_commands(&tokens, &cmd);
		if (!cmd)
		{
			free_cmd_list(head, 0);
			return (NULL);
		}
		if (tokens && tokens->type == T_PIPE)
		{
			tokens = tokens->next;
			cmd = append_cmd_node(cmd);
			if (!cmd)
			{
				free_cmd_list(head, 0);
				return (NULL);
			}
		}
	}
	return (head);
}
