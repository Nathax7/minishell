/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 02:36:30 by nagaudey          #+#    #+#             */
/*   Updated: 2025/05/09 16:42:41 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	check_exec_file(t_exec *exec, char *cmd)
{
	if (access(cmd, F_OK) == -1)
		free_pipex(exec, 127, cmd, "no such file or directory");
	if (access(cmd, X_OK) == -1)
		free_pipex(exec, 126, cmd, "Permission denied");
	exec->pipex.cmd = cmd;
}

void	check_exec(t_exec *exec, char *cmd)
{
	if (access(cmd, F_OK) == -1)
		free_pipex(exec, 127, cmd, "Command not found");
	if (access(cmd, X_OK) == -1)
		free_pipex(exec, 126, cmd, "Permission denied");
}

void	find_path(t_exec *exec, char *cmd)
{
	int		i;
	char	*tmp;

	i = -1;
	if (access(cmd, F_OK) == 0)
	{
		check_exec_file(exec, cmd);
		return ;
	}
	while (exec->pipex.envp && exec->pipex.paths[++i])
	{
		tmp = ft_strjoin(exec->pipex.paths[i], "/");
		if (!tmp)
			free_pipex(exec, 1, "malloc", strerror(errno));
		exec->pipex.cmd = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!exec->pipex.cmd)
			free_pipex(exec, 1, "malloc", strerror(errno));
		if (access(exec->pipex.cmd, F_OK) == 0)
			break ;
		free(exec->pipex.cmd);
		exec->pipex.cmd = NULL;
	}
	if (exec->pipex.cmd)
		check_exec(exec, exec->pipex.cmd);
}

void	execute_bonus(t_exec *exec, char *argv, char **envp)
{
	exec->pipex.cmd_args = ft_split(argv, ' ');
	if (exec->pipex.cmd_args[0] == NULL)
		free_pipex(exec, 127, argv, "Command not found");
	find_path(exec, exec->pipex.cmd_args[0]);
	if (!exec->pipex.cmd)
		free_pipex(exec, 127, exec->pipex.cmd_args[0], "Command not found");
	if (execve(exec->pipex.cmd, exec->pipex.cmd_args, envp) == -1)
	{
		if (errno == EACCES || errno == EISDIR)
			free_pipex(exec, 126, "pipex: execve", strerror(errno));
		if (errno == ENOENT || errno == EPERM)
			free_pipex(exec, 127, "pipex: execve", strerror(errno));
		if (errno == ENOTDIR)
			free_pipex(exec, 127, "pipex: execve", strerror(errno));
		free_pipex(exec, 1, "execve", strerror(errno));
	}
}
