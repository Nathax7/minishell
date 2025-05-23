/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipeline_group.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:56:23 by nagaudey          #+#    #+#             */
/*   Updated: 2025/05/23 16:13:51 by nagaudey         ###   ########.fr       */
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

// static void	free_exec_list(t_exec *head)
// {
// 	t_exec	*next;

// 	while (head)
// 	{
// 		next = head->next;
// 		if (head->group)
// 		{
// 			for (int i = 0; head->group[i]; ++i)
// 				free(head->group[i]);
// 			free(head->group);
// 		}
// 		free(head);
// 		head = next;
// 	}
// }

static int	finalize_group_node(t_exec *node, char **cmds, int ncmd)
{
	node->group = ft_calloc(ncmd + 1, sizeof(*node->group));
	if (!node->group)
		return (-1);
	for (int i = 0; i < ncmd; ++i)
	{
		node->group[i] = ft_strdup(cmds[i]);
		if (!node->group[i])
		{
			while (i-- > 0)
				free(node->group[i]);
			free(node->group);
			return (-1);
		}
	}
	node->group[ncmd] = NULL;
	return (0);
}

t_exec	*split_pipeline_groups(t_token *tokens)
{
	int		max;
	char	**cmds;
	t_exec	*head;
	t_exec	*current;
	int		ncmd;

	max = find_size(tokens);
	if (max <= 0)
		return (NULL);
	cmds = ft_calloc(max + 1, sizeof(*cmds));
	if (!cmds)
		return (NULL);
	head = NULL;
	current = append_exec_node(&head);
	if (!current)
	{
		free(cmds);
		return (NULL);
	}
	ncmd = 0;
	while (tokens)
	{
		if ((tokens->type == T_REDIRECT_IN || tokens->type == T_HEREDOC)
			&& tokens->next)
		{
			if (current->infile_name)
				free(current->infile_name);
			current->heredoc = (tokens->type == T_HEREDOC);
			tokens = tokens->next;
			current->infile_name = ft_strdup(tokens->value);
			open_infile_exec(current, current->infile_name);
			tokens = tokens->next;
		}
		else if ((tokens->type == T_REDIRECT_OUT || tokens->type == T_APPEND)
			&& tokens->next)
		{
			if (current->outfile_name)
				free(current->outfile_name);
			current->append = (tokens->type == T_APPEND);
			tokens = tokens->next;
			current->outfile_name = ft_strdup(tokens->value);
			open_outfile_exec(current, current->outfile_name, 0);
			tokens = tokens->next;
			if (!(tokens && (tokens->type == T_REDIRECT_OUT
						|| tokens->type == T_APPEND)))
			{
				if (finalize_group_node(current, cmds, ncmd) < 0)
					break ;
				current = append_exec_node(&head);
				if (!current)
					break ;
				ncmd = 0;
			}
		}
		else if (tokens->type == T_PIPE)
		{
			tokens = tokens->next;
			//ncmd++;
		}
		else
		{
			cmds[ncmd++] = tokens->value;
			// cmds[ncmd++] = ft_strjoin_with_space(tokens->value);
			tokens = tokens->next;
		}
	}
	if (ncmd > 0)
		finalize_group_node(current, cmds, ncmd);
	free(cmds);
	return (head);
}
