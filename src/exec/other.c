/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:38:10 by nagaudey          #+#    #+#             */
/*   Updated: 2025/05/09 16:42:41 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

// void	check_exec(t_cmd *cmd, char *path)
// {
// 	if (access(path, F_OK) == -1)
// 		free_cmd(cmd, 127, NULL, path);
// 	if (access(path, X_OK) == -1)
// 		free_cmd(cmd, 126, NULL, path);
// }

// void	find_path(t_cmd *cmd, char *path)
// {
// 	int		i;
// 	char	*tmp;
// 	char	*full_path;

// 	if (access(path, F_OK) == 0)
// 	{
// 		check_exec(cmd, path);
// 		cmd->cmd = ft_strdup(path);
// 		if (!cmd->cmd)
// 			free_cmd(cmd, 1, NULL, "Error malloc");
// 		return ;
// 	}
// 	i = 0;
// 	while (cmd->paths && cmd->paths[i])
// 	{
// 		tmp = ft_strjoin(cmd->paths[i], "/");
// 		if (!tmp)
// 			free_cmd(cmd, 1, NULL, "Error malloc");

// 		full_path = ft_strjoin(tmp, path);
// 		free(tmp);
// 		if (!full_path)
// 			free_cmd(cmd, 1, NULL, "Error malloc");

// 		if (access(full_path, F_OK) == 0)
// 		{
// 			check_exec(cmd, full_path);
// 			cmd->cmd = full_path;
// 			return ;
// 		}
// 		free(full_path);
// 		i++;
// 	}
// 	free_cmd(cmd, 127, NULL, path);
// }

// void	execute(t_cmd *cmd, char **envp)
// {
// 	cmd->cmd_args = ft_split(argv, ' ');
// 	if (cmd->cmd_args[0] == NULL)
// 		free_cmd(cmd, 127, NULL, "Error execve");
// 	find_path(cmd, cmd->cmd_args[0]);
// 	if (!cmd->cmd)
// 		free_cmd(cmd, 127, NULL, cmd->cmd_args[0]);
// 	if (execve(cmd->cmd, cmd->cmd_args, envp) == -1)
// 	{
// 		if (errno == EACCES || errno == EISDIR)
// 			free_cmd(cmd, 126, NULL, "Error execve");
// 		if (errno == ENOENT || errno == EPERM)
// 			free_cmd(cmd, 127, NULL, "Error execve");
// 		if (errno == ENOTDIR)
// 			free_cmd(cmd, 127, NULL, "Error execve");
// 		free_cmd(cmd, 1, NULL, "Error execve");
// 	}
// }

// void init_path(t_cmd *cmd, char **envp)
// {
// 	int i;

// 	i = 0;
// 	while (envp && envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
// 			i++;
// 	if (!envp || !envp[i])
// 	{
// 		cmd->env = NO_ENV;
// 		return ;
// 	}
// 	cmd->paths = ft_split(envp[i] + 5, ':');
// 	if (!cmd->paths)
// 		free_cmd(cmd, 1, NULL, "Error malloc");
// }

// void init_file(t_exec *exec, t_type type)
// {
// 	if (type == INFILE)
// 		open_infile(exec, exec->pipex.infile_name);
// 	if (type == APPEND)
// 		open_outfile(exec, exec->pipex.outfile_name, 0);
// 	else if (type == OUTFILE)
// 		open_outfile(exec, exec->pipex.outfile, 1);
// }

// int	exec(char **envp, int cmd_nbr, char **line)
// {
// 	t_cmd cmd;
// 	int i;
// 	int i_wait;

// 	i = 0;
// 	i_wait = 0;
// 	while (line && line[i])
// 	{
// 		if (line[i] == "<")
// 		{
// 			i++;
// 			cmd.file = ft_strdup(line[i]);
// 			init_file(&cmd, INFILE);
// 			i++;
// 		}
// 		if ()
// 	}
// 	while (cmd->next != NULL)
// 	{
// 		if (cmd->type == INFILE || cmd->type == HEREDOC)
// 			init_file(cmd);
// 		while (++i < cmd_nbr)
// 			child_process(cmd, envp, cmd_nbr, i);
// 		cmd = cmd->next;
// 	}
// 	cmd = first;
// 	while (i_wait < cmd_nbr)
// 	{
// 		waitpid(cmd->pid, &cmd->status, 0);
// 		cmd = cmd->next;
// 		i++;
// 	}
// 	free_cmd(first, -1, NULL, NULL);
// 	if (WIFEXITED(first->status))
// 		return (WEXITSTATUS(first->status));
// 	return (first->status);
// }

