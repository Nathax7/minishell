/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 22:58:16 by nagaudey          #+#    #+#             */
/*   Updated: 2025/06/19 21:28:40 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	setup_redirections(t_exec *exec, int cmd_index)
{
	if (cmd_index == 0)
	{
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
		else
		{
			if (dup2(exec->pipes[0][1], STDOUT_FILENO) == -1)
				free_child(exec, 1, "dup2", strerror(errno));
		}
	}
	else if (cmd_index == exec->cmd_count - 1)
	{
		if (exec->cmd_list->fd_input != -1)
		{
			if (dup2(exec->cmd_list->fd_input, STDIN_FILENO) == -1)
				free_child(exec, 1, "dup2", strerror(errno));
		}
		else
		{
			if (dup2(exec->pipes[cmd_index - 1][0], STDIN_FILENO) == -1)
				free_child(exec, 1, "dup2", strerror(errno));
		}
		if (exec->cmd_list->fd_output != -1)
		{
			if (dup2(exec->cmd_list->fd_output, STDOUT_FILENO) == -1)
				free_child(exec, 1, "dup2", strerror(errno));
		}
	}
	else if (cmd_index != exec->cmd_count - 1)
	{
		if (exec->cmd_list->fd_input != -1)
		{
			if (dup2(exec->cmd_list->fd_input, STDIN_FILENO) == -1)
				free_child(exec, 1, "dup2", strerror(errno));
		}
		else
		{
			if (dup2(exec->pipes[cmd_index - 1][0], STDIN_FILENO) == -1)
				free_child(exec, 1, "dup2", strerror(errno));
		}
		if (exec->cmd_list->fd_output != -1)
		{
			if (dup2(exec->cmd_list->fd_output, STDOUT_FILENO) == -1)
				free_child(exec, 1, "dup2", strerror(errno));
		}
		else
		{
			if (dup2(exec->pipes[cmd_index][1], STDOUT_FILENO) == -1)
				free_child(exec, 1, "dup2", strerror(errno));
		}
	}
}


void	execute_child(t_exec *exec, int cmd_index, char **envp)
{
	struct_open_infile(exec);
	struct_open_outfile(exec);
	setup_redirections(exec, cmd_index);
	close_all_pipes(exec);
	execute_bonus(exec, envp);
}

void	child_process(t_exec *exec, int cmd_index, char **envp)
{
	exec->cmd_list->files = find_first_files(exec->cmd_list->files);
	exec->pids[cmd_index] = fork();
	if (exec->pids[cmd_index] == -1)
		free_child(exec, 1, "pid", strerror(errno));
	if (exec->pids[cmd_index] == 0)
		execute_child(exec, cmd_index, envp);
}
