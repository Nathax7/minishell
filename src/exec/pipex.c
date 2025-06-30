/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 00:01:49 by nagaudey          #+#    #+#             */
/*   Updated: 2025/06/29 20:59:36 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	usage(void)
{
	ft_message("minishell", NULL, "Bad argument");
	ft_putstr_fd("Ex: ./minishell <file1> <cmd1> <cmd2> <...> <file2>\n", 1);
	ft_putstr_fd("    ./minishell \"here_doc\" <LIMITER> <cmd> <cmd1>"
					"<...> <file>\n",
					1);
	return (-1);
}

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
	{
		ft_message("minishell", NULL, "Error create_pipes");
		free_parent(exec, 1);
	}
	i = 0;
	while (i < exec->cmd_count - 1)
	{
		exec->pipes[i] = ft_calloc(2, sizeof(int));
		if (!exec->pipes[i])
		{
			free_pipes(exec, i);
			ft_message("minishell", NULL, "Error create_pipes");
			free_parent(exec, 1);
		}
		if (pipe(exec->pipes[i]) == -1)
		{
			free(exec->pipes[i]);
			free_pipes(exec, i);
			ft_message("Error create_pipes", NULL, NULL);
			free_parent(exec, 1);
		}
		i++;
	}
}

int	pipex(t_token *tokens, char **envp)
{
	t_exec	exec;
	int		i;
	t_cmd	*current_cmd;
	t_cmd	*saved_head;
	int		final_exit_status;

	exec_init(&exec, envp);
	parsing_exec(tokens, &exec);
	if (!exec.cmd_list)
		return (1);
	exec.cmd_count = find_size_cmd(exec.cmd_list);
	if (exec.cmd_count < 1)
		return (usage());
	if (exec.cmd_count == 1 && exec.cmd_list->is_builtin)
	{
		final_exit_status = execute_single_builtin_in_parent(&exec, envp);
		return (final_exit_status);
	}
	exec.pids = malloc(sizeof(pid_t) * exec.cmd_count);
	if (!exec.pids)
		return (1);
	create_pipes(&exec);
	i = -1;
	current_cmd = exec.cmd_list;
	while (++i < exec.cmd_count)
	{
		saved_head = exec.cmd_list;
		exec.cmd_list = current_cmd;
		child_process(&exec, i, envp);
		exec.cmd_list = saved_head;
		current_cmd = current_cmd->next;
	}
	close_all_pipes(&exec);
	i = -1;
	final_exit_status = 0;
	while (++i < exec.cmd_count)
	{
		waitpid(exec.pids[i], &exec.exit_status, 0);
		if (i == exec.cmd_count - 1)
		{
			if (WIFEXITED(exec.exit_status))
				final_exit_status = WEXITSTATUS(exec.exit_status);
			else
				final_exit_status = exec.exit_status;
		}
	}
	free(exec.pids);
	return (final_exit_status);
}
