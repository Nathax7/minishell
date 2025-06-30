/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 20:03:17 by almeekel          #+#    #+#             */
/*   Updated: 2025/06/29 20:53:43 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

static void cleanup_parent_cmd_path(t_exec *exec)
{
	if (exec->cmd_list && exec->cmd_list->cmd_path)
	{
		free(exec->cmd_list->cmd_path);
		exec->cmd_list->cmd_path = NULL;
	}
}

static void cleanup_parent_fds(t_exec *exec)
{
	if (exec->stdin_backup != -1)
	{
		dup2(exec->stdin_backup, STDIN_FILENO);
		close(exec->stdin_backup);
		exec->stdin_backup = -1;
	}
	if (exec->stdout_backup != -1)
	{
		dup2(exec->stdout_backup, STDOUT_FILENO);
		close(exec->stdout_backup);
		exec->stdout_backup = -1;
	}
}
void free_parent(t_exec *exec, int status)
{
	if (!exec)
		return;
	cleanup_parent_cmd_path(exec);
	cleanup_child_resources(exec);
	cleanup_parent_fds(exec);
	reset_exec_state(exec);
	if (status != -1)
		exit(status);
}