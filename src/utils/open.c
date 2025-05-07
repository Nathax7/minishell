/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:23:18 by nagaudey          #+#    #+#             */
/*   Updated: 2025/05/07 15:24:48 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	open_infile(t_pipex *pipex, char *infile)
{
	if (access(infile, F_OK) == -1)
	{
		free_pipex(pipex, 1, "No such file or directory", infile);
	}
	if (access(infile, R_OK) == -1)
	{
		free_pipex(pipex, 1, "permission denied", infile);
		return ;
	}
	pipex->infile = open(infile, O_RDONLY);
	if (pipex->infile == -1)
		free_pipex(pipex, 1, "<open_infile>", strerror(errno));
}

void	open_outfile(t_pipex *pipex, char *outfile, int mode)
{
	if (access(outfile, F_OK) == 0)
	{
		if (access(outfile, W_OK) == -1)
			free_pipex(pipex, 1, "permission denied", outfile);
	}
	if (mode == 0)
		pipex->outfile = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (mode == 1)
		pipex->outfile = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile == -1)
		free_pipex(pipex, 1, "<open_outfile>", strerror(errno));
}

void	open_infile_exec(t_exec *exec, char *infile)
{
	if (access(infile, F_OK) == -1)
	{
		free_exec(exec, 1, "No such file or directory", infile);
	}
	if (access(infile, R_OK) == -1)
	{
		free_exec(exec, 1, "permission denied", infile);
		return ;
	}
	exec->infile = open(infile, O_RDONLY);
	if (exec->infile == -1)
		free_exec(exec, 1, "<open_infile>", strerror(errno));
}

void	open_outfile_exec(t_exec *exec, char *outfile, int mode)
{
	if (access(outfile, F_OK) == 0)
	{
		if (access(outfile, W_OK) == -1)
			free_exec(exec, 1, "permission denied", outfile);
	}
	if (mode == 0)
		exec->outfile = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (mode == 1)
		exec->outfile = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (exec->outfile == -1)
		free_exec(exec, 1, "<open_outfile>", strerror(errno));
}