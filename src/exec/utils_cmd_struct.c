/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmd_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 20:08:48 by nagaudey          #+#    #+#             */
/*   Updated: 2025/08/18 14:23:37 by almeekel         ###   ########.fr       */
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
	new_node->fd_input = -1;
	new_node->fd_output = -1;
	new_node->is_builtin = 0;
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

t_files	*new_infile_node(char *value, int heredoc, char ***envp_ptr)
{
	t_files	*new_node;

	(void)envp_ptr;
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
