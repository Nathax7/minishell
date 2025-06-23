/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 22:58:16 by nagaudey          #+#    #+#             */
/*   Updated: 2025/06/23 19:16:54 by almeekel         ###   ########.fr       */
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
				free_child(exec, 1, "dup21", strerror(errno));
		}
		if (exec->cmd_list->fd_output != -1)
		{
			if (dup2(exec->cmd_list->fd_output, STDOUT_FILENO) == -1)
				free_child(exec, 1, "dup22", strerror(errno));
		}
		else if (exec->cmd_count > 1)
		{
			if (dup2(exec->pipes[0][1], STDOUT_FILENO) == -1)
				free_child(exec, 1, "dup23", strerror(errno));
		}
	}
	else if (cmd_index == exec->cmd_count - 1)
	{
		if (exec->cmd_list->fd_input != -1)
		{
			if (dup2(exec->cmd_list->fd_input, STDIN_FILENO) == -1)
				free_child(exec, 1, "dup24", strerror(errno));
		}
		else
		{
			if (dup2(exec->pipes[cmd_index - 1][0], STDIN_FILENO) == -1)
				free_child(exec, 1, "dup25", strerror(errno));
		}
		if (exec->cmd_list->fd_output != -1)
		{
			if (dup2(exec->cmd_list->fd_output, STDOUT_FILENO) == -1)
				free_child(exec, 1, "dup26", strerror(errno));
		}
	}
	else
	{
		if (exec->cmd_list->fd_input != -1)
		{
			if (dup2(exec->cmd_list->fd_input, STDIN_FILENO) == -1)
				free_child(exec, 1, "dup27", strerror(errno));
		}
		else
		{
			if (dup2(exec->pipes[cmd_index - 1][0], STDIN_FILENO) == -1)
				free_child(exec, 1, "dup28", strerror(errno));
		}
		if (exec->cmd_list->fd_output != -1)
		{
			if (dup2(exec->cmd_list->fd_output, STDOUT_FILENO) == -1)
				free_child(exec, 1, "dup29", strerror(errno));
		}
		else
		{
			if (dup2(exec->pipes[cmd_index][1], STDOUT_FILENO) == -1)
				free_child(exec, 1, "dup211", strerror(errno));
		}
	}
}

void	close_child_pipes(t_exec *exec)
{
    int i;

    i = 0;
    while (i < exec->cmd_count - 1)
    {
        close(exec->pipes[i][0]);
        close(exec->pipes[i][1]);
        i++;
    }
}

void	close_parent_pipes(t_exec *exec, int cmd_index)
{
    if (cmd_index == 0 && exec->cmd_count > 1)
        close(exec->pipes[0][1]);
    else if (cmd_index > 0)
    {
        close(exec->pipes[cmd_index - 1][0]);
        if (cmd_index < exec->cmd_count - 1)
            close(exec->pipes[cmd_index][1]);
    }
}

void	execute_child(t_exec *exec, int cmd_index, char **envp)
{
	struct_open_infile(exec);
	struct_open_outfile(exec);
	setup_redirections(exec, cmd_index);
	close_child_pipes(exec);
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
	close_parent_pipes(exec, cmd_index);
}
