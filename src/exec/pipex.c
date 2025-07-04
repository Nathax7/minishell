/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 00:01:49 by nagaudey          #+#    #+#             */
/*   Updated: 2025/07/04 17:10:54 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	free_pipes(t_exec *exec, int failed_index)
{
	int	j;

	j = 0;
	while (j < failed_index)
	{
		if (exec->pipes[j])
		{
			if (exec->pipes[j][0] != -1)
				close(exec->pipes[j][0]);
			if (exec->pipes[j][1] != -1)
				close(exec->pipes[j][1]);
			free(exec->pipes[j]);
		}
		j++;
	}
	free(exec->pipes);
	exec->pipes = NULL;
}

void	create_pipes(t_exec *exec)
{
	int	i;

	if (!exec || exec->cmd_count <= 1)
		return ;
	exec->pipes = ft_calloc(exec->cmd_count - 1, sizeof(int *));
	if (!exec->pipes)
		free_parent(exec, 1, "Error create_pipes", NULL);
	i = 0;
	while (i < exec->cmd_count - 1)
	{
		exec->pipes[i] = ft_calloc(2, sizeof(int));
		if (!exec->pipes[i])
		{
			free_pipes(exec, i);
			free_parent(exec, 1, "Error create_pipes", NULL);
		}
		if (pipe(exec->pipes[i]) == -1)
		{
			free(exec->pipes[i]);
			free_pipes(exec, i);
			free_parent(exec, 1, "Error create_pipes", NULL);
		}
		i++;
	}
}

int	pipex(t_token *tokens, char ***envp_ptr)
{
	t_exec	exec;
	int		i;
	t_cmd	*head;
	int		sig;

	exec_init(&exec, *envp_ptr);
	parsing_exec(tokens, &exec);
	if (!exec.cmd_list)
		return (1);
	exec.cmd_count = find_size_cmd(exec.cmd_list);
	head = exec.cmd_list;
	if (exec.cmd_count == 1 && exec.cmd_list->is_builtin)
	{
		exec.exit_status = execute_single_builtin_in_parent(&exec, envp_ptr);
		return (exec.exit_status);
	}
	setup_parent_signals();
	exec.pids = malloc(sizeof(pid_t) * exec.cmd_count);
	if (!exec.pids)
		return (1);
	create_pipes(&exec);
	i = -1;
	while (++i < exec.cmd_count)
	{
		child_process(&exec, i, *envp_ptr);
		exec.cmd_list = exec.cmd_list->next;
	}
	i = -1;
	close_all_pipes(&exec);
	while (++i < exec.cmd_count)
	{
		waitpid(exec.pids[i], &exec.exit_status, 0);
		if (WIFSIGNALED(exec.exit_status))
		{
			sig = WTERMSIG(exec.exit_status);
			if (sig == SIGINT)
			{
				g_signal_test = 130;
				ft_putchar_fd('\n', STDOUT_FILENO);
			}
			else if (sig == SIGQUIT)
			{
				g_signal_test = 131;
				ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
			}
		}
	}
	exec.cmd_list = head;
	free_parent(&exec, -1, NULL, NULL);
	setup_interactive_signals();
	if (WIFEXITED(exec.exit_status))
		return (WEXITSTATUS(exec.exit_status));
	return (exec.exit_status);
}
