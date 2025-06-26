/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:57:50 by nagaudey          #+#    #+#             */
/*   Updated: 2025/06/25 22:16:12 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	is_directory(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

int	has_path_component(const char *cmd)
{
	return (ft_strchr(cmd, '/') != NULL);
}

void	check_path(t_exec *exec)
{
	char	*cmd;

	cmd = exec->cmd_list->args->cmd_args;
	if (!has_path_component(cmd))
		return ;
	if (access(cmd, F_OK) == -1)
		free_child(exec, 127, cmd, "No such file or directory");
	if (is_directory(cmd))
		free_child(exec, 126, cmd, "Is a directory");
	if (access(cmd, X_OK) == -1)
		free_child(exec, 126, cmd, "Permission denied");
	return ;
}

int	is_builtin(t_exec *exec, char **envp)
{
	if (!exec)
		return (0);
	if (ft_strcmp(exec->cmd_list->args->cmd_args, "echo") == 0)
		builtin_echo(exec->cmd_list->args);
	else if (ft_strcmp(exec->cmd_list->args->cmd_args, "cd") == 0)
		builtin_cd(exec->cmd_list->args, &envp);
	else if (ft_strcmp(exec->cmd_list->args->cmd_args, "pwd") == 0)
		builtin_pwd();
	else if (ft_strcmp(exec->cmd_list->args->cmd_args, "export") == 0)
		builtin_export(exec->cmd_list->args, &envp);
	else if (ft_strcmp(exec->cmd_list->args->cmd_args, "unset") == 0)
		builtin_unset(exec->cmd_list->args, &envp);
	else if (ft_strcmp(exec->cmd_list->args->cmd_args, "env") == 0)
		builtin_env(&envp);
	else if (ft_strcmp(exec->cmd_list->args->cmd_args, "exit") == 0)
		builtin_exit(exec->cmd_list->args);
	else
		return (0);
	return (1);
}
