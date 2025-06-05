/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipeline_group.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:56:23 by nagaudey          #+#    #+#             */
/*   Updated: 2025/06/05 17:55:43 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

static t_exec	*append_exec_node(t_exec **head)
{
	t_exec	*node;
	t_exec	*last;

	node = malloc(sizeof(*node));
	if (!node)
		return (NULL);
	node->group = NULL;
	node->infile_name = NULL;
	node->outfile_name = NULL;
	node->infile = STDIN_FILENO;
	node->outfile = STDOUT_FILENO;
	node->append = 0;
	node->heredoc = 0;
	node->next = NULL;
	node->prev = NULL;
	if (!*head)
		*head = node;
	else
	{
		last = find_last(*head);
		last->next = node;
		node->prev = last;
	}
	return (node);
}

static void	free_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->max)
	{
		if (cmd->cmds[i])
		{
			free(cmd->cmds[i]);
			cmd->cmds[i] = NULL;
		}
		i++;
	}
	free(cmd->cmds);
}

static int	finalize_group_node(t_exec **node, char **cmds, int ncmd)
{
	int	i;

	i = 0;
	(*node)->group = ft_calloc(ncmd + 1, sizeof(*(*node)->group));
	if (!(*node)->group)
		return (1);
	while (i < ncmd)
	{
		(*node)->group[i] = ft_strdup(cmds[i]);
		if (!(*node)->group[i])
		{
			while (i-- > 0)
				free((*node)->group[i]);
			free((*node)->group);
			return (1);
		}
		i++;
	}
	(*node)->group[ncmd] = NULL;
	return (0);
}

static int	add_to_cmds(char **cmds, int ncmd, const char *value)
{
	char	*tmp;

	if (!cmds[ncmd])
	{
		cmds[ncmd] = ft_strdup(value);
		if (!cmds[ncmd])
			return (1);
	}
	else
	{
		tmp = ft_strjoin_space(cmds[ncmd], value);
		if (!tmp)
			return (1);
		free(cmds[ncmd]);
		cmds[ncmd] = tmp;
	}
	return (0);
}

void	handle_input(t_token **tokens, t_exec **current)
{
	if ((*current)->infile_name)
		free((*current)->infile_name);
	(*current)->heredoc = ((*tokens)->type == T_HEREDOC);
	(*tokens) = (*tokens)->next;
	(*current)->infile_name = ft_strdup((*tokens)->value);
	open_infile_exec(*current, (*current)->infile_name);
	(*tokens) = (*tokens)->next;
}

void	handle_output(t_token **tokens, t_exec **current)
{
	if ((*current)->outfile_name)
		free((*current)->outfile_name);
	(*current)->append = ((*tokens)->type == T_APPEND);
	(*tokens) = (*tokens)->next;
	(*current)->outfile_name = ft_strdup((*tokens)->value);
	open_outfile_exec(*current, (*current)->outfile_name, 0);
	(*tokens) = (*tokens)->next;
}

int	handle_infile(t_token **tokens, t_exec **current, t_exec **head, t_cmd *cmd)
{
	if ((*current)->outfile_name)
	{
		if (finalize_group_node(current, cmd->cmds, cmd->ncmd + 1))
		return (1);
		(*current) = append_exec_node(head);
		if (!(*current))
		return (1);
		cmd->ncmd = 0;
		(*tokens) = (*tokens)->next;
		if (((*tokens)->type == T_REDIRECT_IN || (*tokens)->type == T_HEREDOC)
			&& (*tokens)->next)
			handle_input(tokens, current);
		else if (((*tokens)->type == T_REDIRECT_OUT
				|| (*tokens)->type == T_APPEND) && (*tokens)->next)
			handle_output(tokens, current);
		while ((*tokens) && (*tokens)->type == T_WORD)
		{
			if (add_to_cmds(cmd->cmds, cmd->ncmd, (*tokens)->value))
				return (1);
			(*tokens) = (*tokens)->next;
		}
	}
	return (0);
}

int	handle_word(t_token **tokens, t_cmd *cmd)
{
	while ((*tokens) && (*tokens)->type == T_WORD)
	{
		if (add_to_cmds(cmd->cmds, cmd->ncmd, (*tokens)->value))
			return (1);
		(*tokens) = (*tokens)->next;
	}
	return (0);
}

t_exec	*parse_loop(t_token **tokens, t_exec **current, t_exec **head,
		t_cmd *cmd)
{
	while (*tokens)
	{
		if (((*tokens)->type == T_REDIRECT_IN || (*tokens)->type == T_HEREDOC)
			&& (*tokens)->next)
			handle_input(tokens, current);
		else if (((*tokens)->type == T_REDIRECT_OUT
				|| (*tokens)->type == T_APPEND) && (*tokens)->next)
			handle_output(tokens, current);
		else if ((*tokens)->type == T_PIPE)
		{
			if (handle_infile(tokens, current, head, cmd))
				break ;
			else
			{
				cmd->ncmd++;
				(*tokens) = (*tokens)->next;
			}
		}
		else if (handle_word(tokens, cmd))
			break ;
	}
	if (++cmd->ncmd > 0)
		finalize_group_node(current, cmd->cmds, cmd->ncmd);
	return (*head);
}

t_exec	*split_pipeline_groups(t_token *tokens)
{
	t_cmd	cmd;
	t_exec	*head;
	t_exec	*current;

	cmd.max = find_size(tokens);
	if (cmd.max <= 0)
		return (NULL);
	cmd.cmds = ft_calloc(cmd.max + 1, sizeof(*cmd.cmds));
	if (!cmd.cmds)
		return (NULL);
	head = NULL;
	current = append_exec_node(&head);
	if (!current)
	{
		free(cmd.cmds);
		return (NULL);
	}
	cmd.ncmd = 0;
	head = parse_loop(&tokens, &current, &head, &cmd);
	free_cmd(&cmd);
	return (head);
}
