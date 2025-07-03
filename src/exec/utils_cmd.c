/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:57:50 by nagaudey          #+#    #+#             */
/*   Updated: 2025/07/03 19:00:12 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	is_directory(t_exec *exec)
{
	struct stat	st;
	char		*cmd_path;

	if (!exec || !exec->cmd_list || !exec->cmd_list->args
		|| !exec->cmd_list->args->cmd_args)
		return (0);
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

int	execute_builtin(t_exec *exec, char ***envp_ptr)
{
	if (!exec || !exec->cmd_list->args || !exec->cmd_list->args->cmd_args)
		return (0);
	if (ft_strcmp(exec->cmd_list->args->cmd_args, "echo") == 0)
		return (builtin_echo(exec->cmd_list->args));
	else if (ft_strcmp(exec->cmd_list->args->cmd_args, "cd") == 0)
		return (builtin_cd(exec->cmd_list->args, envp_ptr));
	else if (ft_strcmp(exec->cmd_list->args->cmd_args, "pwd") == 0)
		return (builtin_pwd());
	else if (ft_strcmp(exec->cmd_list->args->cmd_args, "export") == 0)
		return (builtin_export(exec->cmd_list->args, envp_ptr));
	else if (ft_strcmp(exec->cmd_list->args->cmd_args, "unset") == 0)
		return (builtin_unset(exec->cmd_list->args, envp_ptr));
	else if (ft_strcmp(exec->cmd_list->args->cmd_args, "env") == 0)
		return (builtin_env(envp_ptr));
	else if (ft_strcmp(exec->cmd_list->args->cmd_args, "exit") == 0)
		return (builtin_exit(exec->cmd_list->args));
	else
		return (0);
}

int	is_builtin(t_args *cmd)
{
	if (!cmd || !cmd->cmd_args)
		return (0);
	if (ft_strcmp(cmd->cmd_args, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd->cmd_args, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd->cmd_args, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd->cmd_args, "export") == 0)
		return (1);
	if (ft_strcmp(cmd->cmd_args, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd->cmd_args, "env") == 0)
		return (1);
	if (ft_strcmp(cmd->cmd_args, "exit") == 0)
		return (1);
	return (0);
}

int	execute_single_builtin_in_parent(t_exec *exec, char ***envp_ptr)
{
    int	saved_stdin;
    int	saved_stdout;
    int	exit_status;

    saved_stdin = -1;
    saved_stdout = -1;
    if (!exec || !exec->cmd_list || !exec->cmd_list->args || !exec->cmd_list->args->cmd_args)
        return (0);

    struct_open_infile(exec);
    struct_open_outfile(exec);

    if (exec->cmd_list->fd_input != -1)
    {
        saved_stdin = dup(STDIN_FILENO);
        if (saved_stdin == -1)
            return (1);
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
            return (1);
        }
        dup2(exec->cmd_list->fd_output, STDOUT_FILENO);
        close(exec->cmd_list->fd_output);
    }

    exit_status = execute_builtin(exec, envp_ptr);

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
    return (exit_status);
}

int	execute_builtin_in_child(t_exec *exec, char **envp)
{
    if (!exec || !exec->cmd_list->args || !exec->cmd_list->args->cmd_args)
        return (0);
    if (ft_strcmp(exec->cmd_list->args->cmd_args, "echo") == 0)
        return (builtin_echo(exec->cmd_list->args));
    else if (ft_strcmp(exec->cmd_list->args->cmd_args, "pwd") == 0)
        return (builtin_pwd());
    else if (ft_strcmp(exec->cmd_list->args->cmd_args, "env") == 0)
        return (builtin_env(&envp));
    else if (ft_strcmp(exec->cmd_list->args->cmd_args, "exit") == 0)
        return (builtin_exit(exec->cmd_list->args));
    else
        return (0);
}
