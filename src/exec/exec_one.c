/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:03:21 by nagaudey          #+#    #+#             */
/*   Updated: 2025/06/29 20:52:51 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	exec_one(t_exec *exec, char **envp)
{
	exec->pids[0] = fork();
	if (exec->pids[0] == -1)
	{
		ft_message("minishell", "fork", strerror(errno));
		free_child(exec, 1);
	}
	if (exec->pids[0] == 0)
	{
		struct_open_infile(exec);
		struct_open_outfile(exec);
		if (exec->cmd_list->fd_input != -1)
		{
			if (dup2(exec->cmd_list->fd_input, STDIN_FILENO) == -1)
			{
				ft_message("minishell", "dup2", strerror(errno));
				free_child(exec, 1);
			}
		}
		if (exec->cmd_list->fd_output != -1)
		{
			if (dup2(exec->cmd_list->fd_output, STDOUT_FILENO) == -1)
			{
				ft_message("minishell", "dup2", strerror(errno));
				free_child(exec, 1);
			}
		}
		execute_bonus(exec, envp);
	}
}
