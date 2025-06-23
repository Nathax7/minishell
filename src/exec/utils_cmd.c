/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:57:50 by nagaudey          #+#    #+#             */
/*   Updated: 2025/06/23 17:26:31 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	is_directory(t_exec *exec)
{
	if (ft_strchr(exec->cmd_list->args->cmd_args, '/'))
	{
		ft_message(exec->cmd_list->args->cmd_args, "Is a directory");
		if (access(exec->cmd_list->args->cmd_args, F_OK) == -1)
			free_child(exec, 127, "minishell: %s: No such file or directory\n",
				exec->cmd_list->args->cmd_args);
		if (access(exec->cmd_list->args->cmd_args, X_OK) == -1)
			free_child(exec, 126, "minishell: %s: Permission denied\n",
				exec->cmd_list->args->cmd_args);
		return (1);
	}
	return (0);
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
