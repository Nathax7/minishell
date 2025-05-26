/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipeline_group.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:56:23 by nagaudey          #+#    #+#             */
/*   Updated: 2025/05/26 19:13:04 by nagaudey         ###   ########.fr       */
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
	int	i;

	i = 0;
	node->group = ft_calloc(ncmd + 1, sizeof(*node->group));
	if (!node->group)
		return (-1);
	while (i < ncmd)
	{
		node->group[i] = ft_strdup(cmds[i]);
		if (!node->group[i])
		{
			while (i-- > 0)
				free(node->group[i]);
			free(node->group);
			return (-1);
		}
		i++;
	}
	node->group[ncmd] = NULL;
	return (0);
}

static int add_to_cmds(char **cmds, int ncmd, const char *value)
{
	char *tmp;

	if (!cmds[ncmd])
	{
		cmds[ncmd] = ft_strdup(value);
		if (!cmds[ncmd])
			return (-1);
	}
	else
	{
		tmp = ft_strjoin_space(cmds[ncmd], value);
		if (!tmp)
			return (-1);
		free(cmds[ncmd]);
		cmds[ncmd] = tmp;
	}
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
		}
		else if (tokens->type == T_PIPE)
		{
			if (current->outfile_name)
			{
				if (finalize_group_node(current, cmds, ncmd + 1) < 0)
					break ;
				// while (i <= ncmd)
				// {
				//     if (cmds[i])
				//     {
				//         free(cmds[i]);
				//         cmds[i] = NULL;
				//     }
				// 	i++;
				// }
				current = append_exec_node(&head);
				if (!current)
					break ;
				ncmd = 0;
				tokens = tokens->next;
				while (tokens && tokens->type == T_WORD)
				{
					if (add_to_cmds(cmds, ncmd, tokens->value) < 0)
						break;
					tokens = tokens->next;
				}
			}
			else
			{
				ncmd++;
				tokens = tokens->next;
			}
		}
		else
		{
			while (tokens && tokens->type == T_WORD)
			{
				if (add_to_cmds(cmds, ncmd, tokens->value) < 0)
					break;
				tokens = tokens->next;
			}
		}
	}
	if (++ncmd > 0)
		finalize_group_node(current, cmds, ncmd);
	free(cmds);
	return (head);
}
