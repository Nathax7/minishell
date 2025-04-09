/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:56:15 by nagaudey          #+#    #+#             */
/*   Updated: 2025/03/31 17:20:19 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(char **argv, char **envp, int *fd, t_pipex *pipex)
{
	int	filein;

	pipex->pid1 = fork();
	if (pipex->pid1 == -1)
		ft_printf_error(1, "pipex: pid: %s\n", strerror(errno));
	if (pipex->pid1 == 0)
	{
		filein = open(argv[1], O_RDONLY);
		if (filein == -1 || dup2(fd[1], STDOUT_FILENO) == -1 || dup2(filein,
				STDIN_FILENO) == -1)
		{
			close(fd[0]);
			close(fd[1]);
			if (filein != -1)
				close(filein);
			ft_printf_error(1, "pipex: filein: %s\n", strerror(errno));
		}
		close(fd[0]);
		close(fd[1]);
		close(filein);
		execute(argv[2], envp);
	}
}

void	child2_process(char **argv, char **envp, int *fd, t_pipex *pipex)
{
	int	fileout;

	pipex->pid2 = fork();
	if (pipex->pid2 == -1)
		ft_printf_error(1, "pipex: pid: %s\n", strerror(errno));
	if (pipex->pid2 == 0)
	{
		fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fileout == -1 || dup2(fd[0], STDIN_FILENO) == -1 || dup2(fileout,
				STDOUT_FILENO) == -1)
		{
			close(fd[1]);
			close(fd[0]);
			if (fileout != -1)
				close(fileout);
			ft_printf_error(1, "pipex: fileout: %s\n", strerror(errno));
		}
		close(fd[1]);
		close(fd[0]);
		close(fileout);
		execute(argv[3], envp);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	int		status;
	t_pipex	pipex;

	if (argc != 5)
	{
		ft_printf_error(-1, "\033[31mError: Bad arguments\n\e[0m", 2);
		ft_printf_error(1, "Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
	}
	if (pipe(fd) == -1)
		ft_printf_error(1, "pipex: pipe: %s\n", strerror(errno));
	child_process(argv, envp, fd, &pipex);
	child2_process(argv, envp, fd, &pipex);
	close(fd[0]);
	close(fd[1]);
	waitpid(pipex.pid1, &status, 0);
	waitpid(pipex.pid2, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (status);
}
