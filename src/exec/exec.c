/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:38:10 by nagaudey          #+#    #+#             */
/*   Updated: 2025/04/18 21:25:27 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

void	check_exec_file(t_cmd *cmd, char *cmd_name)
{
	if (access(cmd_name, F_OK) == -1)
		free_cmd(cmd, 127, NULL, cmd_name);
	if (access(cmd_name, X_OK) == -1)
		free_cmd(cmd, 126, NULL, cmd_name);
	cmd->cmd = cmd_name;
}

void	check_exec(t_cmd *cmd, char *cmd_name)
{
	if (access(cmd_name, F_OK) == -1)
		free_cmd(cmd, 127, NULL, cmd_name);
	if (access(cmd_name, X_OK) == -1)
		free_cmd(cmd, 126, NULL, cmd_name);
}

void	find_path(t_cmd *cmd, char *cmd_name)
{
	int		i;
	char	*tmp;

	i = -1;
	if (access(cmd_name, F_OK) == 0)
		return (check_exec_file(cmd, cmd_name));
	while (cmd->env && cmd->paths[++i])
	{
		tmp = ft_strjoin(cmd->paths[i], "/");
		if (!tmp)
			free_cmd(cmd, 1, NULL, "Error strjoin");
		cmd->cmd = ft_strjoin(tmp, cmd_name);
		free(tmp);
		if (!cmd->cmd)
			free_cmd(cmd, 1, NULL, "Error strjoin");
		if (access(cmd->cmd, F_OK) == 0)
			break ;
		free(cmd->cmd);
		cmd->cmd = NULL;
	}
	if (cmd->cmd)
		check_exec(cmd, cmd->cmd);
}

void	execute(t_cmd *cmd, char *argv, char **envp)
{
	cmd->cmd_args = ft_split(argv, ' ');
	if (cmd->cmd_args[0] == NULL)
		free_cmd(cmd, 127, NULL, argv);
	find_path(cmd, cmd->cmd_args[0]);
	if (!cmd->cmd)
		free_cmd(cmd, 127, NULL, cmd->cmd_args[0]);
	if (execve(cmd->cmd, cmd->cmd_args, envp) == -1)
	{
		if (errno == EACCES || errno == EISDIR)
			free_cmd(cmd, 126, NULL, "Error execve");
		if (errno == ENOENT || errno == EPERM)
			free_cmd(cmd, 127, NULL, "Error execve");
		if (errno == ENOTDIR)
			free_cmd(cmd, 127, NULL, "Error execve");
		free_cmd(cmd, 1, NULL, "Error execve");
	}
}
