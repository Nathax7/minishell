/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 22:58:16 by nagaudey          #+#    #+#             */
/*   Updated: 2025/03/31 03:15:41 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	setup_redirections(t_pipex *pipex)
{
	if (pipex->i == 0)
	{
		if (dup2(pipex->infile, STDIN_FILENO) == -1)
			free_parent(pipex, 1, "pipex: dup2: %s\n", strerror(errno));
		if (dup2(pipex->fd[1], STDOUT_FILENO) == -1)
			free_parent(pipex, 1, "pipex: dup2: %s\n", strerror(errno));
		close(pipex->infile);
		close(pipex->outfile);
	}
	else if (pipex->i == pipex->cmd_nbr - 1)
	{
		if (dup2(pipex->outfile, STDOUT_FILENO) == -1)
			free_parent(pipex, 1, "pipex: dup2: %s\n", strerror(errno));
		close(pipex->outfile);
		close(pipex->infile);
	}
	else
	{
		if (dup2(pipex->fd[1], STDOUT_FILENO) == -1)
			free_parent(pipex, 1, "pipex: dup2: %s\n", strerror(errno));
		close(pipex->outfile);
		close(pipex->infile);
	}
	close(pipex->fd[1]);
}

void	execute_child(t_pipex *pipex, char *argv, char **envp)
{
	close(pipex->fd[0]);
	setup_redirections(pipex);
	execute_bonus(pipex, argv, envp);
}

void	child_process(t_pipex *pipex, char *argv, char **envp)
{
	if (pipe(pipex->fd) == -1)
		free_parent(pipex, 1, "pipex: pipe: %s\n", strerror(errno));
	pipex->pids[pipex->i] = fork();
	if (pipex->pids[pipex->i] == -1)
		free_parent(pipex, 1, "pipex: pid: %s\n", strerror(errno));
	if (pipex->pids[pipex->i] == 0)
		execute_child(pipex, argv, envp);
	close(pipex->fd[1]);
	if (dup2(pipex->fd[0], STDIN_FILENO) == -1)
		free_parent(pipex, 1, "pipex: dup2: %s\n", strerror(errno));
	close(pipex->fd[0]);
}
