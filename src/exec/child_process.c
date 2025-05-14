/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 22:58:16 by nagaudey          #+#    #+#             */
/*   Updated: 2025/05/12 19:50:57 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	setup_redirections(t_exec *exec)
{
	if (exec->pipex.i == 0 && exec->infile_name[exec->i] != NULL)
	{
		if (dup2(exec->pipex.infile, STDIN_FILENO) == -1)
		free_pipex(exec, 1, "dup2", strerror(errno));
		if (dup2(exec->pipex.fd[1], STDOUT_FILENO) == -1)
		free_pipex(exec, 1, "dup2", strerror(errno));
		close(exec->pipex.infile);
		close(exec->pipex.outfile);
	}
	else if (exec->pipex.i == exec->pipex.cmd_nbr - 1 && exec->outfile_name[exec->i] != NULL)
	{
		if (dup2(exec->pipex.outfile, STDOUT_FILENO) == -1)
		free_pipex(exec, 1, "dup2", strerror(errno));
		close(exec->pipex.outfile);
		close(exec->pipex.infile);
	}
	else if (exec->pipex.i != exec->pipex.cmd_nbr - 1)
	{
		if (dup2(exec->pipex.fd[1], STDOUT_FILENO) == -1)
			free_pipex(exec, 1, "dup2", strerror(errno));
		close(exec->pipex.outfile);
		close(exec->pipex.infile);
	}
	close(exec->pipex.fd[1]);
}

void	execute_child(t_exec *exec, char *argv, char **envp)
{
	close(exec->pipex.fd[0]);
	setup_redirections(exec);
	execute_bonus(exec, argv, envp);
}

void	child_process(t_exec *exec, char *argv, char **envp)
{
	if (pipe(exec->pipex.fd) == -1)
		free_pipex(exec, 1, "pipe", strerror(errno));
	exec->pipex.pids[exec->pipex.i] = fork();
	if (exec->pipex.pids[exec->pipex.i] == -1)
		free_pipex(exec, 1, "pid", strerror(errno));
	if (exec->pipex.pids[exec->pipex.i] == 0)
		execute_child(exec, argv, envp);
	close(exec->pipex.fd[1]);
	if (dup2(exec->pipex.fd[0], STDIN_FILENO) == -1)
		free_pipex(exec, 1, "dup2", strerror(errno));
	close(exec->pipex.fd[0]);
}
