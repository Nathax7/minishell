/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:03:21 by nagaudey          #+#    #+#             */
/*   Updated: 2025/06/23 18:27:16 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	exec_one(t_exec *exec, char **envp)
{
    struct_open_infile(exec);
    struct_open_outfile(exec);
    if (is_builtin(exec, envp) == 0)
    {
        exec->pids[0] = fork();
        if (exec->pids[0] == -1)
            free_child(exec, 1, "pid", strerror(errno));
        if (exec->pids[0] == 0)
        {
            if (exec->cmd_list->fd_input != -1)
            {
                if (dup2(exec->cmd_list->fd_input, STDIN_FILENO) == -1)
                    free_child(exec, 1, "dup21", strerror(errno));
                close(exec->cmd_list->fd_input);
            }
            if (exec->cmd_list->fd_output != -1)
            {
                if (dup2(exec->cmd_list->fd_output, STDOUT_FILENO) == -1)
                    free_child(exec, 1, "dup22", strerror(errno));
                close(exec->cmd_list->fd_output);
            }
            execute_bonus(exec, envp);
        }
        if (exec->cmd_list->fd_input != -1)
            close(exec->cmd_list->fd_input);
        if (exec->cmd_list->fd_output != -1)
            close(exec->cmd_list->fd_output);
		return (1);
    }
    if (exec->stdin_backup >= 0)
    {
        if (dup2(exec->stdin_backup, STDIN_FILENO) == -1)
            ft_message("dup2", "Failed to restore stdin");
    }
    if (exec->stdout_backup >= 0)
    {
        if (dup2(exec->stdout_backup, STDOUT_FILENO) == -1)
            ft_message("dup2", "Failed to restore stdout");
    }
	return (0);
}
