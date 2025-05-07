/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 02:36:30 by nagaudey          #+#    #+#             */
/*   Updated: 2025/05/07 15:17:58 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	check_exec_file(t_pipex *pipex, char *cmd)
{
	if (access(cmd, F_OK) == -1)
		free_pipex(pipex, 127, cmd, "no such file or directory");
	if (access(cmd, X_OK) == -1)
		free_pipex(pipex, 126, cmd, "Permission denied");
	pipex->cmd = cmd;
}

void	check_exec(t_pipex *pipex, char *cmd)
{
	if (access(cmd, F_OK) == -1)
		free_pipex(pipex, 127, cmd, "Command not found");
	if (access(cmd, X_OK) == -1)
		free_pipex(pipex, 126, cmd, "Permission denied");
}

void	find_path(t_pipex *pipex, char *cmd)
{
	int		i;
	char	*tmp;

	i = -1;
	if (access(cmd, F_OK) == 0)
	{
		check_exec_file(pipex, cmd);
		return ;
	}
	while (pipex->envp && pipex->paths[++i])
	{
		tmp = ft_strjoin(pipex->paths[i], "/");
		if (!tmp)
			free_pipex(pipex, 1, "malloc", strerror(errno));
		pipex->cmd = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!pipex->cmd)
			free_pipex(pipex, 1, "malloc", strerror(errno));
		if (access(pipex->cmd, F_OK) == 0)
			break ;
		free(pipex->cmd);
		pipex->cmd = NULL;
	}
	if (pipex->cmd)
		check_exec(pipex, pipex->cmd);
}

void	execute_bonus(t_pipex *pipex, char *argv, char **envp)
{
	pipex->cmd_args = ft_split(argv, ' ');
	if (pipex->cmd_args[0] == NULL)
		free_pipex(pipex, 127, argv, "Command not found");
	find_path(pipex, pipex->cmd_args[0]);
	if (!pipex->cmd)
		free_pipex(pipex, 127, pipex->cmd_args[0], "Command not found");
	if (execve(pipex->cmd, pipex->cmd_args, envp) == -1)
	{
		if (errno == EACCES || errno == EISDIR)
			free_pipex(pipex, 126, "pipex: execve", strerror(errno));
		if (errno == ENOENT || errno == EPERM)
			free_pipex(pipex, 127, "pipex: execve", strerror(errno));
		if (errno == ENOTDIR)
			free_pipex(pipex, 127, "pipex: execve", strerror(errno));
		free_pipex(pipex, 1, "execve", strerror(errno));
	}
}
