/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 22:58:16 by nagaudey          #+#    #+#             */
/*   Updated: 2025/06/25 22:46:13 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	setup_redirections(t_exec *exec, int cmd_index)
{
	if (!exec || !exec->cmd_list)
	{
		free_child(exec, 1, "setup_redirections", "Invalid exec structure");
		return ;
	}
	if (cmd_index > 0 && (!exec->pipes || !exec->pipes[cmd_index - 1]))
	{
		free_child(exec, 1, "setup_redirections", "Invalid pipe structure");
		return ;
	}
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
			if (cmd_index > 0 && exec->pipes[cmd_index - 1][0] != -1)
			{
				if (dup2(exec->pipes[cmd_index - 1][0], STDIN_FILENO) == -1)
					free_child(exec, 1, "dup25", strerror(errno));
			}
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
			if (cmd_index > 0 && exec->pipes[cmd_index - 1][0] != -1)
			{
				if (dup2(exec->pipes[cmd_index - 1][0], STDIN_FILENO) == -1)
					free_child(exec, 1, "dup28", strerror(errno));
			}
		}
		if (exec->cmd_list->fd_output != -1)
		{
			if (dup2(exec->cmd_list->fd_output, STDOUT_FILENO) == -1)
				free_child(exec, 1, "dup29", strerror(errno));
		}
		else
		{
			if (cmd_index < exec->cmd_count - 1 && exec->pipes[cmd_index][1] !=
				-1)
			{
				if (dup2(exec->pipes[cmd_index][1], STDOUT_FILENO) == -1)
					free_child(exec, 1, "dup211", strerror(errno));
			}
		}
	}
}

void	close_child_pipes(t_exec *exec, int cmd_index)
{
	int i;

	if (!exec->pipes)
		return;

	i = 0;
	while (i < exec->cmd_count - 1)
	{
		if (!(i == cmd_index - 1 && exec->cmd_list->fd_input == -1) &&
			exec->pipes[i][0] != -1)
		{
			close(exec->pipes[i][0]);
			exec->pipes[i][0] = -1;
		}
		if (!(i == cmd_index && exec->cmd_list->fd_output == -1) &&
			exec->pipes[i][1] != -1)
		{
			close(exec->pipes[i][1]);
			exec->pipes[i][1] = -1;
		}
		i++;
	}
}

void	close_parent_pipes(t_exec *exec, int cmd_index)
{
	if (cmd_index > 0 && exec->pipes[cmd_index - 1][0] != -1)
	{
		close(exec->pipes[cmd_index - 1][0]);
		exec->pipes[cmd_index - 1][0] = -1;
	}
	if (cmd_index < exec->cmd_count - 1 && exec->pipes[cmd_index][1] != -1)
	{
		close(exec->pipes[cmd_index][1]);
		exec->pipes[cmd_index][1] = -1;
	}
}

void	execute_child(t_exec *exec, int cmd_index, char **envp)
{
	struct_open_infile(exec);
	struct_open_outfile(exec);
	setup_redirections(exec, cmd_index);
	close_child_pipes(exec, cmd_index);
	execute_bonus(exec, envp);
}

void	child_process(t_exec *exec, int cmd_index, char **envp)
{
	if (!exec || !exec->cmd_list)
	{
		free_child(exec, 1, "child_process", "Invalid exec structure");
		return ;
	}
	exec->cmd_list->files = find_first_files(exec->cmd_list->files);
	exec->pids[cmd_index] = fork();
	if (exec->pids[cmd_index] == -1)
		free_child(exec, 1, "pid", strerror(errno));
	if (exec->pids[cmd_index] == 0)
		execute_child(exec, cmd_index, envp);
}
