/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:35:41 by nagaudey          #+#    #+#             */
/*   Updated: 2025/07/24 16:03:13 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	check_input_and_output(t_exec *exec, int *saved_stdin, int *saved_stdout)
{
	if (exec->cmd_list->fd_input == -2 || exec->cmd_list->fd_output == -2)
		return (1);
	if (exec->cmd_list->fd_input != -1)
	{
		*saved_stdin = dup(STDIN_FILENO);
		if (*saved_stdin == -1)
			return (1);
		dup_and_close(&exec->cmd_list->fd_input, STDIN_FILENO);
	}
	if (exec->cmd_list->fd_output != -1)
	{
		*saved_stdout = dup(STDOUT_FILENO);
		if (*saved_stdout == -1)
		{
			if (*saved_stdin != -1)
			{
				dup_and_close(saved_stdin, STDIN_FILENO);
			}
			return (1);
		}
		dup_and_close(&exec->cmd_list->fd_output, STDOUT_FILENO);
	}
	return (0);
}

int	execute_single_builtin_in_parent(t_exec *exec, char ***envp_ptr)
{
	int	saved_stdin;
	int	saved_stdout;
	int	exit_status;

	saved_stdin = -1;
	saved_stdout = -1;
	if (!exec || !exec->cmd_list || !exec->cmd_list->args
		|| !exec->cmd_list->args->cmd_args)
		return (0);
	struct_open_infile(exec);
	struct_open_outfile(exec);
	check_input_and_output(exec, &saved_stdin, &saved_stdout);
	exit_status = execute_builtin(exec, envp_ptr);
	if (saved_stdin != -1)
	{
		dup_and_close(&saved_stdin, STDIN_FILENO);
	}
	if (saved_stdout != -1)
	{
		dup_and_close(&saved_stdout, STDOUT_FILENO);
	}
	return (exit_status);
}
