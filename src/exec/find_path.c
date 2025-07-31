/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:31:06 by nagaudey          #+#    #+#             */
/*   Updated: 2025/07/30 18:14:46 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	check_exec_file(t_exec *exec, char *cmd)
{
	struct stat	st;

	if (access(cmd, F_OK) == -1)
		free_child(exec, 127, cmd, "No such file or directory");
	if (stat(cmd, &st) == 0 && S_ISDIR(st.st_mode)
		&& ft_strchr(exec->cmd_list->args->cmd_args, '/'))
		free_child(exec, 126, cmd, "Is a directory");
	if (stat(cmd, &st) == 0 && S_ISDIR(st.st_mode)
		&& !ft_strchr(exec->cmd_list->args->cmd_args, '/'))
		free_child(exec, 127, cmd, "command not found");
	if (access(cmd, X_OK) == -1)
		free_child(exec, 126, cmd, "Permission denied");
	exec->cmd_list->cmd_path = ft_strdup(cmd);
	if (!exec->cmd_list->cmd_path)
		free_child(exec, 1, "malloc", strerror(errno));
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
	if (ft_strchr(cmd, '/') || access(cmd, F_OK) == 0)
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
