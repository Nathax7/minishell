/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:23:16 by nagaudey          #+#    #+#             */
/*   Updated: 2025/07/24 13:33:30 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	secure_dup(int old_fd, int new_fd, t_exec *exec)
{
	if (dup2(old_fd, new_fd) == -1)
	{
		free_child(exec, 1, "dup2", strerror(errno));
	}
}

void	setup_pipe_redirections(t_exec *exec, int cmd_index)
{
	if (cmd_index == 0)
	{
		if (exec->cmd_list->fd_input != -1)
			secure_dup(exec->cmd_list->fd_input, STDIN_FILENO, exec);
		if (exec->cmd_list->fd_output != -1)
			secure_dup(exec->cmd_list->fd_output, STDOUT_FILENO, exec);
		else if (exec->cmd_count > 1)
			secure_dup(exec->pipes[0][1], STDOUT_FILENO, exec);
	}
	else if (cmd_index == exec->cmd_count - 1)
	{
		if (exec->cmd_list->fd_input != -1)
			secure_dup(exec->cmd_list->fd_input, STDIN_FILENO, exec);
		else
			secure_dup(exec->pipes[cmd_index - 1][0], STDIN_FILENO, exec);
		if (exec->cmd_list->fd_output != -1)
			secure_dup(exec->cmd_list->fd_output, STDOUT_FILENO, exec);
	}
	else
	{
		secure_dup(exec->pipes[cmd_index - 1][0], STDIN_FILENO, exec);
		secure_dup(exec->pipes[cmd_index][1], STDOUT_FILENO, exec);
	}
}
