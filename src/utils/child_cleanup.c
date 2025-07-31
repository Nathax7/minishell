/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 20:02:40 by almeekel          #+#    #+#             */
/*   Updated: 2025/07/28 13:31:50 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	cleanup_child_resources(t_exec *exec)
{
	if (exec->paths)
	{
		free_split(exec->paths);
		exec->paths = NULL;
	}
	if (exec->pids)
	{
		free(exec->pids);
		exec->pids = NULL;
	}
	if (exec->pipes)
	{
		close_all_pipes(exec);
		exec->pipes = NULL;
	}
}

void	close_child_fds(t_exec *exec)
{
	if (exec->stdin_backup != -1)
	{
		safe_close(&exec->stdin_backup);
		exec->stdin_backup = -1;
	}
	if (exec->stdout_backup != -1)
	{
		safe_close(&exec->stdout_backup);
		exec->stdout_backup = -1;
	}
	if (exec->cmd_list->fd_input != -1)
	{
		safe_close(&exec->cmd_list->fd_input);
		exec->cmd_list->fd_input = -1;
	}
	if (exec->cmd_list->fd_output != -1)
	{
		safe_close(&exec->cmd_list->fd_output);
		exec->cmd_list->fd_output = -1;
	}
}

void	free_child(t_exec *exec, int status, char *str1, char *str2)
{
	if (!exec)
	{
		if (status != -1)
			exit(status);
		return ;
	}
	if (str1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str1, 2);
		if (str2)
			ft_putstr_fd(": ", 2);
		else
			ft_putstr_fd("\n", 2);
	}
	if (str2)
	{
		ft_putstr_fd(str2, 2);
		ft_putstr_fd("\n", 2);
	}
	close_child_fds(exec);
	cleanup_cmd_list(exec, 0);
	cleanup_child_resources(exec);
	if (status != -1)
		exit(status);
}
