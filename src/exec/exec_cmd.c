/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:47:43 by nagaudey          #+#    #+#             */
/*   Updated: 2025/06/19 16:01:52 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

char	**struct_to_array(t_args *args)
{
	char	**array;
	t_args	*current;
	int		size;
	int		i;

	if (!args)
		return (NULL);
	size = find_size_args(args);
	array = malloc(sizeof(char *) * (size + 1));
	if (!array)
		return (NULL);
	current = args;
	i = 0;
	while (current && i < size)
	{
		array[i] = current->cmd_args;
		current = current->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

void	check_exec_file(t_exec *exec, char *cmd)
{
	if (access(cmd, F_OK) == -1)
		free_child(exec, 127, cmd, "No such file or directory");
	if (access(cmd, X_OK) == -1)
		free_child(exec, 126, cmd, "Permission denied");
	exec->cmd_list->cmd_path = cmd;
}

void	check_exec(t_exec *exec, char *cmd)
{
	if (access(cmd, F_OK) == -1)
		free_child(exec, 127, cmd, "command not found");
	if (access(cmd, X_OK) == -1)
		free_child(exec, 126, cmd, "Permission denied");
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
	while (exec->paths && exec->envp && exec->paths[++i])
	{
		tmp = ft_strjoin(exec->paths[i], "/");
		if (!tmp)
			free_child(exec, 1, "malloc", strerror(errno));
		exec->cmd_list->cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!exec->cmd_list->cmd_path)
			free_child(exec, 1, "malloc", strerror(errno));
		if (access(exec->cmd_list->cmd_path, F_OK) == 0)
			break ;
		free(exec->cmd_list->cmd_path);
		exec->cmd_list->cmd_path = NULL;
	}
	if (exec->cmd_list->cmd_path)
		check_exec(exec, exec->cmd_list->cmd_path);
}

void	execute_bonus(t_exec *exec, char **envp)
{
	exec->cmd_list->args = find_first_args(exec->cmd_list->args);
	if (exec->cmd_list->args->cmd_args == NULL)
		free_child(exec, 127, exec->cmd_list->args->cmd_args,
			"Command not found");
	if (is_directory(exec) == 1)
		return ;
	if (is_builtin(exec) == 0)
	{
		find_path(exec, exec->cmd_list->args->cmd_args);
		if (!exec->cmd_list->cmd_path)
			free_child(exec, 127, exec->cmd_list->args->cmd_args,
				"Command not found");
		if (execve(exec->cmd_list->cmd_path,
				struct_to_array(exec->cmd_list->args), envp) == -1)
		{
			if (errno == EACCES || errno == EISDIR)
				free_child(exec, 126, "pipex: execve", strerror(errno));
			if (errno == ENOENT || errno == EPERM)
				free_child(exec, 127, "pipex: execve", strerror(errno));
			if (errno == ENOTDIR)
				free_child(exec, 127, "pipex: execve", strerror(errno));
			free_child(exec, 1, "execve", strerror(errno));
		}
	}
}
