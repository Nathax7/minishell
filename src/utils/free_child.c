/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 20:02:40 by almeekel          #+#    #+#             */
/*   Updated: 2025/06/30 17:28:30 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

static void	cleanup_child_cmd_list(t_exec *exec)
{
	if (exec->cmd_list)
	{
		exec->cmd_list = find_first_cmd(exec->cmd_list);
		free_cmd_list(exec->cmd_list, 0);
		exec->cmd_list = NULL;
	}
}

void	cleanup_child_resources(t_exec *exec)
{
	if (exec->paths)
	{
		free_split(exec->paths);
		exec->paths = NULL;
	}
	if (exec->pids)
	{
		free(exec->pids);
		exec->pids = NULL;
	}
	if (exec->pipes)
	{
		close_all_pipes(exec);
		exec->pipes = NULL;
	}
}

static void	cleanup_child_fds(t_exec *exec)
{
	if (exec->stdin_backup != -1)
	{
		close(exec->stdin_backup);
		exec->stdin_backup = -1;
	}
	if (exec->stdout_backup != -1)
	{
		close(exec->stdout_backup);
		exec->stdout_backup = -1;
	}
}

void	reset_exec_state(t_exec *exec)
{
	exec->envp = NULL;
	exec->cmd_count = 0;
	exec->exit_status = 0;
	exec->envp_exists = 0;
}

void	free_child(t_exec *exec, int status)
{
	if (!exec)
	{
		if (status != -1)
			exit(status);
		return ;
	}
	cleanup_child_cmd_list(exec);
	cleanup_child_resources(exec);
	cleanup_child_fds(exec);
	reset_exec_state(exec);
	if (status != -1)
		exit(status);
}