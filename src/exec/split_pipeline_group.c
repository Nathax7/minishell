/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipeline_group.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:56:23 by nagaudey          #+#    #+#             */
/*   Updated: 2025/05/15 20:50:26 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

static t_exec	*new_exec_node(void)
{
	t_exec	*node;

	node = malloc(sizeof(t_exec));
	if (!node)
		return (NULL);
	node->group = NULL;
	node->infile_name = NULL;
	node->outfile_name = NULL;
	node->append = 0;
	node->next = NULL;
	return (node);
}

static int	is_token(const char *tok, const char *s)
{
	return (ft_strcmp(tok, s) == 0);
}

static int	finalize_group_node(t_exec *node, char **cmds, int ncmd)
{
	int	i;

	node->group = ft_calloc(ncmd + 1, sizeof(char *));
	if (!node->group)
		return (-1);
	for (i = 0; i < ncmd; ++i)
		node->group[i] = ft_strdup(cmds[i]);
	node->group[ncmd] = NULL;
	return (0);
}

t_exec	*split_pipeline_groups(char **tokens)
{
	int		count;
	int		i;
	t_exec	*head;
	t_exec	*current;
	char	**cmds;
	int		ncmd;

	count = 0;
	head = NULL;
	current = NULL;
	ncmd = 0;
	while (tokens[count])
		count++;
	if (count == 0)
		return (NULL);
	cmds = ft_calloc(count + 1, sizeof(char *));
	if (!cmds)
		return (NULL);
	head = new_exec_node();
	if (!head)
		return (free(cmds), NULL);
	current = head;
	i = 0;
	while (i < count)
	{
		if (is_token(tokens[i], "<") && i + 1 < count)
		{
			current->infile_name = ft_strdup(tokens[i + 1]);
			i += 2;
		}
		else if ((is_token(tokens[i], ">") || is_token(tokens[i], ">>")) && i
			+ 1 < count)
		{
			current->outfile_name = ft_strdup(tokens[i + 1]);
			if (is_token(tokens[i], ">>"))
				current->append = 1;
			i += 2;
			if (!(i < count && is_token(tokens[i], ">")))
			{
				if (finalize_group_node(current, cmds, ncmd) < 0)
					break ;
				current->next = new_exec_node();
				if (!current->next)
					break ;
				current = current->next;
				ncmd = 0;
			}
		}
		else if (is_token(tokens[i], "|"))
		{
			i++;
		}
		else
		{
			cmds[ncmd++] = tokens[i];
			i++;
		}
	}
	if (ncmd > 0)
		finalize_group_node(current, cmds, ncmd);
	free(cmds);
	return (head);
}
