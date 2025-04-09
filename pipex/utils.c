/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 19:48:57 by nagaudey          #+#    #+#             */
/*   Updated: 2025/04/08 15:01:10 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_double(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	if (access(cmd, F_OK) == 0)
		return (cmd);
	while (envp && envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (path && access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	ft_free_double(paths);
	return (0);
}

void	execute(char *argv, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	if (cmd[0] == NULL)
	{
		ft_free_double(cmd);
		ft_printf_error(127, "pipex: %s: Command not found\n", argv);
	}
	path = find_path(cmd[0], envp);
	if (!path)
	{
		ft_free_double(cmd);
		ft_printf_error(127, "pipex: %s: Command not found\n", argv);
	}
	if (execve(path, cmd, envp) == -1)
	{
		ft_free_double(cmd);
		if (errno == EACCES || errno == EISDIR)
			ft_printf_error(126, "pipex: execve: %s\n", strerror(errno));
		if (errno == ENOENT || errno == EPERM)
			ft_printf_error(127, "pipex: execve: %s\n", strerror(errno));
		ft_printf_error(1, "pipex: execve: %s\n", strerror(errno));
	}
}
