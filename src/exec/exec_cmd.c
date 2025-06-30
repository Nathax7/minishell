/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:47:43 by nagaudey          #+#    #+#             */
/*   Updated: 2025/06/30 20:44:19 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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
		array[i] = ft_strdup(current->cmd_args);
		if (!array[i])
		{
			while (--i >= 0)
				free(array[i]);
			free(array);
			return (NULL);
		}
		current = current->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

void	check_exec_file(t_exec *exec, char *cmd)
{
	struct stat	st;

	if (access(cmd, F_OK) == -1)
		free_child(exec, 127, NULL, NULL);
	if (stat(cmd, &st) == 0 && S_ISDIR(st.st_mode))
		free_child(exec, 126, NULL, NULL);
	if (access(cmd, X_OK) == -1)
		free_child(exec, 126, NULL, NULL);
	exec->cmd_list->cmd_path = cmd;
}

void	check_exec(t_exec *exec, char *cmd)
{
	struct stat	st;

	if (access(cmd, F_OK) == -1)
	{
		free_child(exec, 127, cmd, "command not found");
	}
	if (stat(cmd, &st) == 0 && S_ISDIR(st.st_mode))
	{
		free_child(exec, 126, cmd, "Is a directory");
	}
	if (access(cmd, X_OK) == -1)
	{
		free_child(exec, 126, cmd, "Permission denied");
	}
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
	char	**args_array;
	int		exit_status;
	int		dir_result;

	exec->cmd_list->args = find_first_args(exec->cmd_list->args);
	if (!exec->cmd_list->args || !exec->cmd_list->args->cmd_args)
		free_child(exec, 127, "command not found", NULL);
	if (exec->cmd_list->fd_input == -2 || exec->cmd_list->fd_output == -2)
		exit(1);
	dir_result = is_directory(exec);
	if (dir_result == 126 || dir_result == 127)
		exit(dir_result);
	if (dir_result == 1)
	{
		exec->cmd_list->cmd_path = exec->cmd_list->args->cmd_args;
		args_array = struct_to_array(exec->cmd_list->args);
		if (!args_array)
			exit(1);
		if (execve(exec->cmd_list->cmd_path, args_array, envp) == -1)
		{
			free_split(args_array);
			if (errno == EISDIR)
				free_child(exec, 126, exec->cmd_list->cmd_path,
					"Is a directory");
			else if (errno == EACCES)
				free_child(exec, 126, exec->cmd_list->cmd_path,
					"Permission denied");
			else
				free_child(exec, 127, exec->cmd_list->cmd_path,
					"No such file or directory");
		}
		free_split(args_array);
	}
	if (exec->cmd_list->is_builtin)
	{
		exit_status = execute_builtin(exec, envp);
		exit(exit_status);
	}
	find_path(exec, exec->cmd_list->args->cmd_args);
	if (!exec->cmd_list->cmd_path)
		free_child(exec, 127, exec->cmd_list->args->cmd_args,
			"command not found");
	args_array = struct_to_array(exec->cmd_list->args);
	if (!args_array)
		exit(1);
	if (execve(exec->cmd_list->cmd_path, args_array, envp) == -1)
	{
		free_split(args_array);
		if (errno == EISDIR)
			free_child(exec, 126, exec->cmd_list->cmd_path, "Is a directory");
		else if (errno == EACCES)
			free_child(exec, 126, exec->cmd_list->cmd_path,
				"Permission denied");
		else
			free_child(exec, 127, exec->cmd_list->cmd_path,
				"No such file or directory");
	}
	free_split(args_array);
}
