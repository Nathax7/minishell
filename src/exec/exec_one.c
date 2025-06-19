/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:03:21 by nagaudey          #+#    #+#             */
/*   Updated: 2025/06/19 19:04:12 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	exec_one(t_exec *exec, char **envp)
{
	exec->pids[0] = fork();
	if (exec->pids[0] == -1)
		free_child(exec, 1, "pid", strerror(errno));
	if (exec->pids[0] == 0)
	{
		
		struct_open_infile(exec);
		struct_open_outfile(exec);
		if (exec->cmd_list->fd_input != -1)
		{
			if (dup2(exec->cmd_list->fd_input, STDIN_FILENO) == -1)
				free_child(exec, 1, "dup2", strerror(errno));
		}
		if (exec->cmd_list->fd_output != -1)
		{
			if (dup2(exec->cmd_list->fd_output, STDOUT_FILENO) == -1)
				free_child(exec, 1, "dup2", strerror(errno));
		}
		execute_bonus(exec, envp);
	}
}
