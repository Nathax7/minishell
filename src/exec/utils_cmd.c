/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:57:50 by nagaudey          #+#    #+#             */
/*   Updated: 2025/06/30 20:03:00 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	is_directory(t_exec *exec)
{
	struct stat	st;
	char		*cmd_path;

	cmd_path = exec->cmd_list->args->cmd_args;
	if (ft_strchr(cmd_path, '/'))
	{
		if (access(cmd_path, F_OK) == -1)
			return (127);
		if (stat(cmd_path, &st) == 0 && S_ISDIR(st.st_mode))
			return (126);
		if (access(cmd_path, X_OK) == -1)
			return (126);
		return (0);
	}
	return (0);
}

int	is_builtin(t_exec *exec, char **envp)
{
	if (!exec)
		return (0);
	if (ft_strcmp(exec->cmd_list->args->cmd_args, "echo") == 0)
		return (builtin_echo(exec->cmd_list->args));
	else if (ft_strcmp(exec->cmd_list->args->cmd_args, "cd") == 0)
		return (builtin_cd(exec->cmd_list->args, &envp));
	else if (ft_strcmp(exec->cmd_list->args->cmd_args, "pwd") == 0)
		return (builtin_pwd());
	else if (ft_strcmp(exec->cmd_list->args->cmd_args, "export") == 0)
		return (builtin_export(exec->cmd_list->args, &envp));
	else if (ft_strcmp(exec->cmd_list->args->cmd_args, "unset") == 0)
		return (builtin_unset(exec->cmd_list->args, &envp));
	else if (ft_strcmp(exec->cmd_list->args->cmd_args, "env") == 0)
		return (builtin_env(&envp));
	else if (ft_strcmp(exec->cmd_list->args->cmd_args, "exit") == 0)
		return (builtin_exit(exec->cmd_list->args));
	else
		return (0);
	return (1);
}

int	execute_single_builtin_in_parent(t_exec *exec, char **envp)
{
	int	saved_stdin;
	int	saved_stdout;
	int	exit_status;

	saved_stdin = -1;
	saved_stdout = -1;
	struct_open_infile(exec);
	struct_open_outfile(exec);
	if (exec->cmd_list->fd_input != -1)
	{
		saved_stdin = dup(STDIN_FILENO);
		if (saved_stdin == -1)
			free_parent(exec, 1, "dup stdin",  strerror(errno));
		dup2(exec->cmd_list->fd_input, STDIN_FILENO);
		close(exec->cmd_list->fd_input);
	}
	if (exec->cmd_list->fd_output != -1)
	{
		saved_stdout = dup(STDOUT_FILENO);
		if (saved_stdout == -1)
		{
			if (saved_stdin != -1)
			{
				dup2(saved_stdin, STDIN_FILENO);
				close(saved_stdin);
			}
			free_parent(exec, 1, "dup stdout", strerror(errno));
		}
		dup2(exec->cmd_list->fd_output, STDOUT_FILENO);
		close(exec->cmd_list->fd_output);
	}
	exit_status = is_builtin(exec, envp);
	if (saved_stdin != -1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
	free_parent(exec, -1, NULL, NULL);
	return (exit_status);
}
