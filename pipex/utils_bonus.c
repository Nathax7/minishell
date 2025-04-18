/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 00:03:03 by nagaudey          #+#    #+#             */
/*   Updated: 2025/04/18 20:30:03 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	pipex_init(t_pipex *pipex, char **envp)
{
	size_t	i;

	*pipex = (t_pipex){0};
	pipex->infile = -1;
	pipex->outfile = -1;
	pipex->here_doc = 1;
	pipex->i = -1;
	pipex->i_wait = -1;
	pipex->envp = 1;
	i = 0;
	while (envp && envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (!envp || !envp[i])
	{
		pipex->envp = 0;
		return ;
	}
	pipex->paths = ft_split(envp[i] + 5, ':');
	if (!pipex->paths)
		if (errno == ENOMEM)
			ft_printf_error(-1, "pipex: malloc: %s\n", strerror(errno));
}

void	free_parent(t_pipex *pipex, int status, char *str, char *arg)
{
	if (pipex->paths)
		ft_freesplit(pipex->paths);
	if (pipex->pids)
		free(pipex->pids);
	if (pipex->infile >= 0)
		close(pipex->infile);
	if (pipex->outfile >= 0)
		close(pipex->outfile);
	if (pipex->fd[0] >= 0)
		close(pipex->fd[0]);
	if (pipex->fd[1] >= 0)
		close(pipex->fd[1]);
	if (pipex->cmd_args)
		ft_freesplit(pipex->cmd_args);
	if (pipex->here_doc == 1)
		if (unlink(pipex->infile_name) == -1)
			ft_printf_error(-1, "pipex: %s: unlink fail\n", pipex->infile_name);
	if (pipex->infile_name && pipex->here_doc == 1)
		free(pipex->infile_name);
	pipex->fd[0] = -1;
	pipex->fd[1] = -1;
	ft_printf_error(status, str, arg);
}

void	open_infile(t_pipex *pipex, char *infile)
{
	if (access(infile, F_OK) == -1)
	{
		free_parent(pipex, 1, "pipex: No such file or directory: %s\n", infile);
	}
	if (access(infile, R_OK) == -1)
	{
		free_parent(pipex, 1, "pipex: permission denied: %s\n", infile);
		return ;
	}
	pipex->infile = open(infile, O_RDONLY);
	if (pipex->infile == -1)
		free_parent(pipex, 1, "pipex: <open_infile>: %s\n", strerror(errno));
}

void	open_outfile(t_pipex *pipex, char *outfile, int mode)
{
	if (access(outfile, F_OK) == 0)
	{
		if (access(outfile, W_OK) == -1)
			free_parent(pipex, 1, "pipex: permission denied: %s\n", outfile);
	}
	if (mode == 0)
		pipex->outfile = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (mode == 1)
		pipex->outfile = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile == -1)
		free_parent(pipex, 1, "pipex: <open_outfile>: %s\n", strerror(errno));
}
