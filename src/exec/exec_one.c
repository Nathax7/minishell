/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:03:21 by nagaudey          #+#    #+#             */
/*   Updated: 2025/05/03 17:20:09 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	exec_one(t_pipex *pipex, char *argv, char **envp)
{
	pipex->pids[pipex->i] = fork();
	if (pipex->pids[pipex->i] == -1)
		free_parent(pipex, 1, "pipex: pid: %s\n", strerror(errno));
	if (pipex->pids[pipex->i] == 0)
	{
		if (dup2(pipex->infile, STDIN_FILENO) == -1)
			free_parent(pipex, 1, "pipex: dup2: %s\n", strerror(errno));
		if (dup2(pipex->outfile, STDOUT_FILENO) == -1)
			free_parent(pipex, 1, "pipex: dup2: %s\n", strerror(errno));
		close(pipex->outfile);
		close(pipex->infile);
		execute_bonus(pipex, argv, envp);
	}
}