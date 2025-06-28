/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:57:50 by nagaudey          #+#    #+#             */
/*   Updated: 2025/06/28 19:57:29 by nagaudey         ###   ########.fr       */
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

void	is_builtin(t_exec *exec, char **envp)
{
	char	*cmd;

	if (!exec || !exec->cmd_list || !exec->cmd_list->args
		|| !exec->cmd_list->args->cmd_args)
		return ;
	cmd = exec->cmd_list->args->cmd_args;
	if (ft_strcmp(cmd, "echo") == 0)
		exec->exit_status = builtin_echo(exec->cmd_list->args);
	else if (ft_strcmp(cmd, "cd") == 0)
		exec->exit_status = builtin_cd(exec->cmd_list->args, &envp);
	else if (ft_strcmp(cmd, "pwd") == 0)
		exec->exit_status = builtin_pwd();
	else if (ft_strcmp(cmd, "export") == 0)
		exec->exit_status = builtin_export(exec->cmd_list->args, &envp);
	else if (ft_strcmp(cmd, "unset") == 0)
		exec->exit_status = builtin_unset(exec->cmd_list->args, &envp);
	else if (ft_strcmp(cmd, "env") == 0)
		exec->exit_status = builtin_env(&envp);
	else if (ft_strcmp(cmd, "exit") == 0)
		exec->exit_status = builtin_exit(exec->cmd_list->args);
	else
		return ;
	if (exec->cmd_count > 1)
		free_child(exec, exec->exit_status, NULL, NULL);
}
