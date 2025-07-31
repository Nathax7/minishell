/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure_cleanup_ext.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 21:11:14 by nagaudey          #+#    #+#             */
/*   Updated: 2025/07/30 16:24:48 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

static void	free_cmd_fd_cleanup(t_cmd *current, int is_parent)
{
	if (!is_parent)
	{
		if (current->fd_input != -1)
		{
			safe_close(&current->fd_input);
			current->fd_input = -1;
		}
		if (current->fd_output != -1)
		{
			safe_close(&current->fd_output);
			current->fd_output = -1;
		}
	}
}

static void	free_cmd_resources(t_cmd *current, int is_parent)
{
	if (current->args)
	{
		current->args = find_first_args(current->args);
		free_args_list(current->args);
		current->args = NULL;
	}
	if (!is_parent && current->cmd_path)
	{
		free(current->cmd_path);
		current->cmd_path = NULL;
	}
	if (current->files)
	{
		current->files = find_first_files(current->files);
		if (is_parent)
			unlink_heredoc(current->files);
		free_files_list(current->files);
		current->files = NULL;
	}
}

void	free_cmd_list(t_cmd *cmd_list, int is_parent)
{
	t_cmd	*current;
	t_cmd	*next;

	if (!cmd_list)
		return ;
	current = cmd_list;
	while (current)
	{
		next = current->next;
		free_cmd_resources(current, is_parent);
		free_cmd_fd_cleanup(current, is_parent);
		free(current);
		current = next;
	}
}

void	cleanup_cmd_list(t_exec *exec, int parent)
{
	if (!parent)
	{
		if (exec->envp)
		{
			free_split(exec->envp);
			exec->envp = NULL;
		}
	}
	if (exec->cmd_list)
	{
		exec->cmd_list = find_first_cmd(exec->cmd_list);
		free_cmd_list(exec->cmd_list, parent);
		exec->cmd_list = NULL;
	}
}
