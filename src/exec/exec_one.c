/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:03:21 by nagaudey          #+#    #+#             */
/*   Updated: 2025/06/04 19:04:11 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	exec_one(t_exec *exec, char *argv, char **envp)
{
	exec->pipex.pids[exec->pipex.i] = fork();
	if (exec->pipex.pids[exec->pipex.i] == -1)
		free_pipex(exec, 1, "pid", strerror(errno));
	if (exec->pipex.pids[exec->pipex.i] == 0)
	{
		if (exec->infile_name != NULL)
		{
			if (dup2(exec->pipex.infile, STDIN_FILENO) == -1)
				free_pipex(exec, 1, "dup2", strerror(errno));
		}
		if (exec->outfile_name != NULL)
		{
			if (dup2(exec->pipex.outfile, STDOUT_FILENO) == -1)
				free_pipex(exec, 1, "dup2", strerror(errno));
		}
		close(exec->pipex.outfile);
		close(exec->pipex.infile);
		execute_bonus(exec, argv, envp);
	}
}
